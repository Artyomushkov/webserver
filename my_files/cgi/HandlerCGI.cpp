#include "HandlerCGI.hpp"

std::string HandlerCGI::getServerNameFromHost(const std::string& host) {

	std::string res;
	size_t pos = host.find(':');
	if (pos == std::string::npos)
		return host;
	res = host.substr(0, pos);
	return res;
}

std::string HandlerCGI::getPortFromHost(const std::string& host) {

	std::string res;
	size_t pos = host.find(':');
	if (pos == std::string::npos)
		return ("80");
	res = host.substr(pos + 1, host.length() - pos - 1);
	return res;
}

std::string HandlerCGI::getScriptFromPath(const std::string& path) {

	std::string res;
	size_t pos = path.rfind('/');
	res = path.substr(pos + 1, path.length() - pos - 1);
	return res;
}

std::string HandlerCGI::myToString(int num) {

	char buf[15];
	sprintf(buf, "%d", num);
	std::string res = std::string(buf);
	return res;
}

std::string HandlerCGI::form_env_string(std::string name, std::string param) {

	std::string res = name + "=" + param;
	return res;
}

std::vector<std::string> HandlerCGI::init_env(Connect *conn) {

	std::vector<std::string> res;
	res.push_back(form_env_string("SERVER_SOFTWARE", "JUM webserv/0.0.1"));
	res.push_back(form_env_string("SERVER_NAME", getServerNameFromHost(conn->
		head.get("host"))));
	res.push_back(form_env_string("GATEWAY_INTERFACE", "CGI/1.1"));
	res.push_back(form_env_string("SERVER_PROTOCOL", "HTTP/1.1"));
	res.push_back(form_env_string("SERVER_PORT", getPortFromHost(conn->head
	.get("host"))));
	res.push_back(form_env_string("REQUEST_METHOD", conn->head.get("method")));
	res.push_back(form_env_string("PATH_INFO", conn->head.get("uri")));
	res.push_back(form_env_string("PATH_TRANSLATED", conn->full_file_path));
	res.push_back(form_env_string("SCRIPT_NAME", getScriptFromPath(conn->head
	.get("uri"))));
	res.push_back(form_env_string("QUERY_STRING", conn->get_str));
	res.push_back(form_env_string("REMOTE_HOST", conn->head.get("host")));
	res.push_back(form_env_string("REMOTE_ADDR", getServerNameFromHost
	(conn->head.get("host"))));
	res.push_back(form_env_string("CONTENT_TYPE", conn->head.get("content-type")));
	res.push_back(form_env_string("CONTENT_LENGTH", conn->head.get
	("content-length")));
	res.push_back(form_env_string("HTTP_COOKIE", conn->head.get("cookies")));

	return res;
}

char** HandlerCGI::form_env(std::vector <std::string>& arrEnv) {

	char** env = new char*[arrEnv.size() + 1];
	for (size_t i = 0; i < arrEnv.size(); ++i) {
		env[i] = new char[arrEnv[i].size() + 1];
		strcpy(env[i], arrEnv[i].c_str());
	}
	env[arrEnv.size()] = 0;
	return env;
}

std::string HandlerCGI::getInterpretator(Connect *conn) {

	std::string scriptName = getScriptFromPath(conn->full_file_path);
	size_t pos = scriptName.find('.');
	if (pos == std::string::npos)
		return std::string();
	std::string extension = scriptName.substr(pos, scriptName.length() -
	pos + 1);
	std::map<std::string, std::string>cgiInters = conn->location->getCGI();
	for (std::map<std::string, std::string>::iterator it = cgiInters.begin();
	it != cgiInters.end(); ++it) {
		if (it->first == extension) {
			return it->second;
		}
	}
	return std::string();
}

void HandlerCGI::forkCGI(int fdIn[2], int fdOut[2], char **env, Connect*
conn, std::string const &path_interpritator) {

	if ((dup2(fdIn[0], 0)) < 0) {
		std::cerr << "dup error" << std::endl;
		exit(1);
	}
	close(fdIn[0]);
	close(fdOut[0]);
	if ((dup2(fdOut[1], 1)) < 0) {
		std::cerr << "dup error 2" << std::endl;
		exit(1);
	}
	close(fdOut[1]);
	char* args[3];
	std::string script = conn->full_file_path;
	args[0] = const_cast<char*>(path_interpritator.c_str());
	args[1] = const_cast<char*>(script.c_str());
	args[2] = NULL;
	int n = execve(args[0], args, env);
	if (n < 0) {
		std::cerr << "execve error" << std::endl;
		exit(1);
	}
	exit(0);
}

void	HandlerCGI::handleCGI(Connect* conn, std::string const
&path_interpritator, std::string& head, std::string& body) {

	std::vector<std::string> envVec = init_env(conn);
	char** env = form_env(envVec);
	int fdIn[2];
	pipe(fdIn);
	int fdOut[2];
	pipe(fdOut);
	if (conn->unChunked.content.len())
		write(fdIn[1], conn->unChunked.content.get_content(), conn->unChunked.content.len());
	else
		write(fdIn[1], conn->contentReq.get_content(), conn->contentReq.len());
	close(fdIn[1]);
	pid_t proc = fork();
	if (proc == -1) {
		std::cerr << "fork crashed" << std::endl;
		exit(1);
	}
	if (proc == 0) {
		forkCGI(fdIn, fdOut, env, conn, path_interpritator);
	}
	int status;
	waitpid(proc, &status, 0);
	if (WEXITSTATUS(status))
		throw std::runtime_error("500");
	std::string str_to_read;
	char buffer[4096];
	size_t ret = 4096;
	while (ret == 4096) {
		memset(buffer, 0, 4096);
		ret = read(fdOut[0], buffer, 4096);
		str_to_read += buffer;
	}
	size_t posOfBody = str_to_read.find("\n\n");
	std::cout << "len "<< posOfBody << std::endl;
	if (posOfBody == std::string::npos)
		throw std::runtime_error("400");
	std::string headFromScript = str_to_read.substr(0, posOfBody);
	body = str_to_read.substr(posOfBody + 2);
	close(fdOut[1]);
	close(fdOut[0]);
	close(fdIn[0]);
	for (size_t i = 0; env[i]; i++) {
		delete[] env[i];
	}
	delete[] env;
	head = "HTTP/1.1 200 OK\r\n";
	head += "Server: " + std::string("JUM webserv/0.0.1") + "\r\n";
	head += "Connection: keep-alive\r\n";
	size_t posNewline = 0;
	size_t oldPos = 0;
	while (posNewline != posOfBody) {
		posNewline = headFromScript.find('\n');
		if (posNewline == std::string::npos)
			posNewline = posOfBody;
		head += headFromScript.substr(oldPos, posNewline - oldPos);
		head += "\r\n";
		oldPos = posNewline + 1;
	}
	head += "Content-Length: " + std::to_string(body.length()) +
			"\r\n";
	head += "\r\n";
	/*send(conn->fds, head.data(), head.length(), 0);
	send(conn->fds, body.data(), body.length(), 0);*/
}
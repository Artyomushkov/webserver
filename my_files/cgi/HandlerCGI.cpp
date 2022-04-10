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

std::string HandlerCGI::getInterpretator(const std::string& script) {

	std::string scriptName = getScriptFromPath(script);
	size_t pos = scriptName.find('.');
	if (pos == std::string::npos)
		return std::string("script name error");
	std::string extension = scriptName.substr(pos + 1, scriptName.length() -
	pos);
	if (extension == "py")
		return (std::string("/usr/local/bin/python3"));
	else if (extension == "pl")
		return (std::string("/usr/bin/perl"));
	else
		return std::string("script name error");
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
//	conn->location->getRoot() +
//						 conn->head.get("uri"); //fix
//	std::string interpretator = getInterpretator(script);
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

void	HandlerCGI::handleCGI(Connect* conn, std::string const &path_interpritator) {

	Content res;

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
	char buffer[30];
	size_t ret = 30;
	while (ret == 30) {
		memset(buffer, 0, 30);
		ret = read(fdOut[0], buffer, 30);
		res.push_back(buffer, ret);
	}
	close(fdOut[1]);
	close(fdOut[0]);
	close(fdIn[0]);
	for (size_t i = 0; env[i]; i++) {
		delete[] env[i];
	}
	delete[] env;
	//return res;
	std::string	head;
	head = "HTTP/1.1 200 OK\r\n";
	head += "Server: " + std::string("JUM webserv/0.0.1") + "\r\n";
	head += "Connection: keep-alive\r\n";
	send(conn->fds, head.data(), head.length(), 0);
	send(conn->fds, res.get_content(), res.len(), 0);

}

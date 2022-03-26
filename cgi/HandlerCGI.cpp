#include "HandlerCGI.hpp"

HandlerCGI::HandlerCGI(Request& request, ServerConfig& config) :
_request(request), _config(config) {}

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

std::vector <std::string> HandlerCGI::init_env() {

	std::vector<std::string> res;
	res.push_back(form_env_string("SERVER_SOFTWARE", "OurWebserver21"));
	res.push_back(form_env_string("SERVER_NAME", "DomainNameOfServer"));
	//IP-адрес сервера или доменное имя, взять от request
	res.push_back(form_env_string("GATEWAY_INTERFACE", "CGI/1.1"));
	res.push_back(form_env_string("SERVER_PROTOCOL", "HTTP/1.1")); //из клиента
	res.push_back(form_env_string("SERVER_PORT", myToString(80))); //порт,
	// взять от request
	res.push_back(form_env_string("REQUEST_METHOD", "GET")); //request
	res.push_back(form_env_string("PATH_INFO", "/path/to/script")); //путь
	// после uri с указанием скрипта
	res.push_back(form_env_string("PATH_TRANSLATED", "/fullpath/tos/script"));
	//полный путь до скрипта с учётом конфига (можно объединить с инфо, но в
	// стандарте так
	res.push_back(form_env_string("SCRIPT_NAME", "smth.cgi")); //имя скрипта,
	// либо с конфига, либо с uri (?)
	res.push_back(form_env_string("QUERY_STRING", "d=123&name=kostia")); // из
	// uri после имени шлюза
	res.push_back(form_env_string("REMOTE_HOST", "client_host"));
	res.push_back(form_env_string("REMOTE_ADDR", "client_ip"));
	res.push_back(form_env_string("CONTENT_TYPE", "html")); // из request
	res.push_back(form_env_string("CONTENT_LENGTH", myToString(10354))); //из
	// request
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

void HandlerCGI::forkCGI(int fdIn[2], int fdOut[2]) {

	if (proc == 0) {
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
		args[0] = "/usr/local/bin/python3";
		args[1] = "/Users/jhizdahr/CLionProjects/webserv/cgi_test/test.py";
		args[2] = NULL;
		int n = execve(args[0], args, env);
		if (n < 0) {
			std::cerr << "execve error" << std::endl;
			exit(1);
		}
		exit(0);
	}
}

Content HandlerCGI::execCGI() {

	std::vector<std::string> envVec = init_env();
	char** env = form_env(envVec);
	int fdIn[2];
	pipe(fdIn);
	int fdOut[2];
	pipe(fdOut);
	std::string str = std::string("blablabla");
	write(fdIn[1], str.c_str(), 10); //write there post body
	close(fdIn[1]);
	pid_t proc = fork();
	if (proc == -1) {
		std::cerr << "fork crashed" << std::endl;
		exit(1);
	}
	if (proc == 0) {
		forkCGI(fdIn, fdOut);
	}
	int status;
	waitpid(proc, &status, 0);
	if (WEXITSTATUS(status)) {
		result += "Error in fork"; //form http page with error
	}
	close(fdIn);
	fileOut = freopen(".tmp", "r", fileOut);
	char buffer[30];
	size_t ret = 1;
	std::string result;
	while (ret) {
		memset(buffer, 0, 30);
		ret = fread(buffer, 30, 1, fileOut);
		result += buffer;
	}
	fclose(fileOut);
	for (size_t i = 0; env[i]; i++) {
		delete[] env[i];
	}
	delete[] env;
	remove(".tmp");
	return Content(result, result.length());
}
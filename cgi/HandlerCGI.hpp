#ifndef WEBSERV_HANDLERCGI_HPP
#define WEBSERV_HANDLERCGI_HPP

#include <vector>
#include <iostream>
#include <cstdio>
#include <unistd.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include "../parser/ServerConfig.hpp"
# include "../http/Content/ContentFile.hpp"
# include "../http/Connect.hpp"

class HandlerCGI {

public:
	ContentFile handleCGI(Connect* conn);

private:
	std::string getServerNameFromHost(const std::string& host);
	std::string getPortFromHost(const std::string& host);
	std::string getScriptFromPath(const std::string& path);
	void forkCGI(int fdIn[2], int fdOut[2], char **env, Connect* conn);
	std::string getInterpretator(const std::string& script);
	std::string myToString(int num);
	std::string	form_env_string(std::string name, std::string param);
	std::vector<std::string> init_env(Connect* conn);
	char**	form_env(std::vector<std::string>& arrEnv);

};


#endif

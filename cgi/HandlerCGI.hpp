#ifndef WEBSERV_HANDLERCGI_HPP
#define WEBSERV_HANDLERCGI_HPP

#include <vector>
#include <iostream>
#include <cstdio>
#include <unistd.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include "../msimon/Request.hpp"
# include "../ServerConfig.hpp"
#include "../msimon/Content.hpp"

class HandlerCGI {

private:
	Head 			_head;
	ServerConfig	_config;

public:
	HandlerCGI(Request& request, ServerConfig& config);
	~HandlerCGI() {}
	Content execCGI();

private:
	HandlerCGI();
	void forkCGI(int fdIn, int fdOut);
	std::string myToString(int num);
	std::string	form_env_string(std::string name, std::string param);
	std::vector<std::string> init_env();
	char**	form_env(std::vector<std::string>& arrEnv);



};


#endif
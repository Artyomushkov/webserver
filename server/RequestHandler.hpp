//
// Created by Uncle Richese on 3/15/22.
//

#ifndef WEBSERV_REQUEST_H
#define WEBSERV_REQUEST_H
#include "ServerConfig.hpp"
#include <vector>
#include <sys/select.h>

class RequestHandler
{
public:
	RequestHandler();
	int get(int fd, std::vector<ServerConfig> servers);
};


#endif //WEBSERV_REQUEST_H

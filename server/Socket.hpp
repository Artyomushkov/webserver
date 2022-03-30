#ifndef WEBSERV_SOCKET_HPP
#define WEBSERV_SOCKET_HPP
#include "../parser/ServerConfig.hpp"
#include <vector>
#include <sys/select.h>

class Socket
{
public:
	int fd;
	std::vector<int> acceptfds;
	int port;
	in_addr_t IP;
	sockaddr_in sockaddr;
	size_t addrlen;
	Socket(ServerConfig server,std::pair<in_addr_t, int> );
	std::vector<ServerConfig> servers;
	void setServer(ServerConfig s);
};


#endif //WEBSERV_SOCKET_HPP

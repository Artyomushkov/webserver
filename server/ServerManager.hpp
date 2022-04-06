#ifndef WEBSERV_SERVERMANAGER_HPP
#define WEBSERV_SERVERMANAGER_HPP
#include <sys/select.h>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include "../parser/ServerConfig.hpp"
#include "Socket.hpp"
#include "../http/Connections.hpp"

#define TIME_OUT 5 //Время ожидания в секундах

class ServerManager
{
private:
	fd_set		readfds;
	Connections		connects;
	void setSockets();
	void addSocket(ServerConfig s, std::pair<in_addr_t, int>);
	void setSelect();
	bool is_serverfd(int);
	void close_allconnections(fd_set* fdset);
	std::vector<Socket>::iterator get_socket(int);
	void close_connections(std::vector<int> arr_conn, fd_set* fdset);
public:
	std::vector<ServerConfig> servers;
	std::vector<Socket> sockets;

	void Launch();
	ServerManager();
	~ServerManager();
};


#endif //WEBSERV_SERVERMANAGER_HPP

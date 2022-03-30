#include "Socket.hpp"

Socket::Socket(ServerConfig s, std::pair<in_addr_t, int>  v)
{
	IP = v.first;
	port = v.second;
	fd = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in sockaddr;
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = v.first;
	sockaddr.sin_port = htons(v.second); // htons is necessary to convert a number to
	// network byte order
	if (bind(fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0) {
		std::cout << "Failed to bind to port:"<< port <<". IP: " << IP <<
		std::endl;
		exit(EXIT_FAILURE);
	}
	if (listen(fd, 10) < 0) {
		std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
		exit(EXIT_FAILURE);
	}
	servers.push_back(s);
}

void Socket::setServer(ServerConfig s)
{
	servers.push_back(s);
}

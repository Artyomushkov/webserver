#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include <vector>
#include "Connections.hpp"
#include "ServerConfig.hpp"

#define ADDR "127.0.0.1"
#define PORT 8080
#define TIME_OUT 5 //Время ожидания в секундах

void	close_connections(std::vector<int> arr_conn, fd_set* fdset)
{
	std::vector<int>::iterator	it = arr_conn.begin();

	while (it != arr_conn.end())
	{
		FD_CLR(*it, fdset);
		close(*it);
		it++;
	}
}

int main()
{
	int					server_fd;
	int					socket_fd;
	struct sockaddr_in	address;
	fd_set				readfds;
	fd_set				b_readfds;
	Connections			connects;
	
	std::vector<ServerConfig>	configs;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    	{perror("socket failed"); exit(EXIT_FAILURE);}
	
	int	temp = 1;
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &temp, sizeof(int)) < 0)
		{perror("socket reinit error"); exit(EXIT_FAILURE);}

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(ADDR);
    address.sin_port = htons( PORT );

    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) < 0)
    	{perror("bind failed"); exit(EXIT_FAILURE);}

	if (listen(server_fd, SOMAXCONN) < 0)
		{perror("listen");exit(EXIT_FAILURE);}

	FD_ZERO(&readfds);
	FD_SET(server_fd, &readfds);

	int				res_select;
	struct timeval	tv; tv.tv_sec = TIME_OUT + 1; tv.tv_usec = 0;
	while (1)
	{
		b_readfds = readfds;
		res_select = select(FD_SETSIZE, &b_readfds, NULL, NULL, &tv);
		if (res_select == 0)
			close_connections(connects.checkTime(TIME_OUT), &readfds);
		else if (res_select > 0)
		{
			for (int i = 0; i < FD_SETSIZE; i++)
			{
				if (FD_ISSET(i, &b_readfds))
				{
					if (i == server_fd)
					{
						if ((socket_fd = accept(i, NULL, NULL)) < 0)
							{ perror("accept"); exit(EXIT_FAILURE);}
						FD_SET(socket_fd, &readfds);
					}
					else
					{
						int res = connects.request(i, configs/*, it->servers*/);
						if (res != 0)
						{
							if (res > 0)
								connects.responce(i);
							FD_CLR(i, &readfds);
							close(i);
						}
					}
				}
			}
			close_connections(connects.checkTime(TIME_OUT), &readfds);
		}
	}
	return 0;
}
#include "ServerManager.hpp"

void ServerManager::Launch()
{
	setSockets();
	setSelect();
}

void ServerManager::setSockets()
{
	for(std::vector<ServerConfig>::iterator s_it = servers.begin();
		s_it != servers.end();
		++s_it)
	{
		for(std::vector<std::pair<in_addr_t, int> >::const_iterator it =
				s_it->getVectorOfAddresses().begin();
				it != s_it->getVectorOfAddresses().end();
				++it)
		{
			addSocket(*s_it, *it);
		}
	}
}

void	ServerManager::close_allconnections(fd_set* fdset)
{
	for (std::vector<Socket>::iterator it = sockets.begin();
		 it != sockets.end();
		 ++it)
	{
		FD_CLR(it->fd, fdset);
		close(it->fd);
	}
}

void	ServerManager::close_connections(std::vector<int> arr_conn, fd_set* fdset)
{
	std::vector<int>::iterator	it = arr_conn.begin();

	while (it != arr_conn.end())
	{
		FD_CLR(*it, fdset);
		close(*it);
		it++;
	}
}

bool ServerManager::is_serverfd(int i)
{
	for (std::vector<Socket>::iterator it = sockets.begin();
	 it != sockets.end();
	 ++it)
	{
		if (it->fd == i)
			return true;
	}
	return false;
}

std::vector<Socket>::iterator ServerManager::get_socket(int fd)
{
	std::vector<Socket>::iterator it;
	for (it = sockets.begin();
		 it != sockets.end();
		 ++it)
	{
		if(it->fd == fd)
			return it;
		for(std::vector<int>::iterator it2 = it->acceptfds.begin();
		it2 != it->acceptfds.end();
		++it2)
		{
			if (*it2 == fd)
				return it;
		}
	}
	return it;
}

void ServerManager::setSelect()
{

	fd_set			loopfds;
	int				connectionfd;
	RequestHandler	requestHandler;
	std::vector<int> all_fds;
	std::vector<Socket>::iterator it;
	struct timeval	tv; tv.tv_sec = TIME_OUT + 1; tv.tv_usec = 0;
	int				res_select;

	FD_ZERO(&readfds);
	for(std::vector<Socket>::iterator it = sockets.begin();
		it != sockets.end();
		++it)
	{
		FD_SET(it->fd, &readfds);
		all_fds.push_back(it->fd);
	}
	for (;;)
	{
		loopfds = readfds;
		res_select = select(FD_SETSIZE, &loopfds, NULL, NULL, &tv);
		if (res_select == 0)
			close_connections(connects.checkTime(TIME_OUT), &readfds);
		else if (res_select > 0)
		{
			for (std::vector<int>::iterator i = all_fds.begin();
			i != all_fds.end(); ++i)
			{
				if (FD_ISSET(*i, &loopfds))
				{
					if (is_serverfd(*i))
					{
						it = get_socket(*i);
						connectionfd = accept(it->fd,
											  (struct sockaddr *) &it->sockaddr,
											  (socklen_t *) &it->addrlen);
						if (connectionfd < 0)
						{
							std::cout << "Failed to grab connection. errno: "
									  << errno << std::endl;
							exit(EXIT_FAILURE);
						}
						int res = connects.request(connectionfd, it->servers);
						if (res != 0)
						{
							if (res > 0)
								connects.responce(connectionfd);
							close(connectionfd);
						}
						else if (res == 0)
						{
							FD_SET(connectionfd, &readfds);
							all_fds.push_back(connectionfd);
							it->acceptfds.push_back(connectionfd);
						}
					}
					else
					{
						it = get_socket(*i);
						int res = connects.request(*i, it->servers);
						if (res != 0)
						{
							if (res > 0)
								connects.responce(*i);
							FD_CLR(*i, &readfds);
							close(*i);
						}
					}
				}
			}
		}
	}
}

ServerManager::ServerManager()
{
}

void ServerManager::addSocket(ServerConfig s, std::pair<in_addr_t, int> p)
{
	for(std::vector<Socket>::iterator it = sockets.begin();
		it != sockets.end();
		++it)
	{
		if (p.second == it->port)
		{
			if (p.first == it->IP)
			{
				it->servers.push_back(s);
				return ;
			}
			else if(it->IP == 0)
			{
				it->servers.push_back(s);
				return ;
			}
			else if(p.first == 0)
			{
				it->servers.push_back(s);
				return ;
			}
		}
	}
	sockets.push_back(Socket(s, p));
}

ServerManager::~ServerManager()
{
	close_allconnections(&readfds);
}

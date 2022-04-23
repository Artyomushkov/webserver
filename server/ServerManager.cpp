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

void	ServerManager::close_connections(std::vector<int> arr_conn, fd_set* fdset, std::map <int, std::vector<ServerConfig> >* all_fds)
{
	std::vector<int>::iterator	it = arr_conn.begin();

	while (it != arr_conn.end())
	{
		FD_CLR(*it, fdset);
		(*all_fds).erase(*it);
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
	std::map < int, std::vector<ServerConfig> > all_fds;
	struct timeval	tv; tv.tv_sec = TIME_OUT + 1; tv.tv_usec = 0;
	int				res_select;

	FD_ZERO(&readfds);
	for(std::vector<Socket>::iterator it = sockets.begin();
		it != sockets.end();
		++it)
		FD_SET(it->fd, &readfds);
	for (;;)
	{
		loopfds = readfds;
		res_select = select(FD_SETSIZE, &loopfds, NULL, NULL, &tv);
		if (res_select == 0)
			close_connections(connects.checkTime(TIME_OUT), &readfds, &all_fds);
		else if (res_select > 0)
		{
			for (int i = 0; i < FD_SETSIZE; i++)
			{
				if (FD_ISSET(i, &loopfds))
				{
					std::vector<Socket>::iterator sockets_it = sockets.begin();
					while (sockets_it != sockets.end())
					{
						if ((*sockets_it).fd == i)
							break ;
						sockets_it++;
					}
					if (sockets_it != sockets.end())
					{
						if ((connectionfd = accept(i, NULL, NULL)) < 0)
							{ perror("accept"); exit(EXIT_FAILURE);}
						FD_SET(connectionfd, &readfds);
						all_fds[connectionfd] = (*sockets_it).servers;
					}
					else if (connects.read_request(i, all_fds[connectionfd]))
					{
						FD_CLR(i, &readfds);
						all_fds.erase(i);
						close(i);
					}
				}
			}
		}
	}
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

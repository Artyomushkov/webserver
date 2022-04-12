/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:37:26 by msimon            #+#    #+#             */
/*   Updated: 2022/04/12 12:36:31 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

int	Connections::request(int fds, std::vector<ServerConfig> const &srvs_config)
{
	Connect*	conn = getConnect(fds);

	if (!conn)
	{
		_connections.insert(std::pair<int, Connect> (fds, Connect(fds)));
		conn = getConnect(fds);
		if (!conn)
		{
			Responce::sending(conn, "500");
			return -1;
		}
	}
	try {
		bool f_soc_close;
		conn->contentReq.read(fds, f_soc_close);
		if (f_soc_close)
			return -2;
		conn->timeReq = time(NULL);
		if (conn->statusReq == 0)
		{
			if (Request::parse_head(conn, srvs_config))
				conn->statusReq = 1;
			else
				return 0;
		}
		if (conn->statusReq == 1)
		{
			if (Connect::down_str(conn->head.get("transfer-encoding")) == "chunked")
			{
				if (chunked_decoding(conn))
					conn->statusReq = 2;
				else
					return 0;
			}
			else if ((size_t)std::atol(conn->head.get("content-length").data()) <= conn->contentReq.len())
				conn->statusReq = 2;
			else
				return 0;	
		}
	}
	catch (std::exception &e) {
		Responce::sending(conn, e.what());
		delConnect(fds);
		return -1;
	}
	return 1;
}

void	Connections::responce(int fds)
{
	Connect*	conn = getConnect(fds);

	if (!conn)
	{
		Responce::sending(conn, "500");
		return ;
	}
	try {
		Responce::sending(conn);
	}
	catch (std::exception &e) {
		Responce::sending(conn, e.what());
	}
	delConnect(fds);
}

std::vector<int>	Connections::checkTime(time_t time_out)
{
	std::vector<int>				res;
	std::map<int, Connect>::iterator	it = _connections.begin();
	time_t										now = time(NULL);

	while (it != _connections.end())
	{
		if (now - it->second.timeReq > time_out)
		{
//			Responce::sending(&(it->second), "408");
			res.push_back(it->first);
			it = _connections.erase(it);
		}
		else
			it++;
	}
	return res;	
}

Connect*	Connections::getConnect(int fds)
{
	std::map<int, Connect>::iterator	it;

	it = _connections.find(fds);
	if (it != _connections.end())
		return &(it->second);
	return NULL;
}

void	Connections::delConnect(int fds)
{
	std::map<int, Connect>::iterator	it;

	it = _connections.find(fds);
	if (it != _connections.end())
		_connections.erase(it);
}

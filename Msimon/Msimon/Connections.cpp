/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 14:37:26 by msimon            #+#    #+#             */
/*   Updated: 2022/04/02 11:13:23 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Connections.hpp"

int	Connections::request(int fds, std::vector<ServerConfig> const &srvs_config)
{
	connect_t*	conn = getConnect(fds);

	if (!conn)
	{
		try {
			_connections.insert(std::pair<int, connect_t> (fds, connect_t(fds)));
		}
		catch (std::exception &e) {
			std::cout << e.what() << "\n";
		}
		conn = getConnect(fds);
		if (!conn)
		{
			Responce::sending(conn, "500");
			return -1;
		}
	}
	try {
		conn->contentReq.read(fds);
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
			if (connect_t::down_str(conn->head.get("transfer-encoding")) == "chunked")
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
	connect_t*	conn = getConnect(fds);

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
	std::map<int, connect_t>::iterator	it = _connections.begin();
	time_t										now = time(NULL);

	while (it != _connections.end())
	{
		if (now - it->second.timeReq > time_out)
		{
			Responce::sending(&(it->second), "408");
			res.push_back(it->first);
			it = _connections.erase(it);
		}
		else
			it++;
	}
	return res;	
}

connect_t*	Connections::getConnect(int fds)
{
	std::map<int, connect_t>::iterator	it;

	it = _connections.find(fds);
	if (it != _connections.end())
		return &(it->second);
	return NULL;
}

void	Connections::delConnect(int fds)
{
	std::map<int, connect_t>::iterator	it;

	it = _connections.find(fds);
	if (it != _connections.end())
		_connections.erase(it);
}

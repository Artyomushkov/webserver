/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 07:29:49 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 11:05:37 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

std::map<int, http::connect_t>	http::_connections;

int	http::run_request(int socket_fd/*, std::vector<ServerConfig> const &srvs_config*/)
{
	http::connect_t*	conn = get_connect(socket_fd);

	if (!conn)
	{
		_connections.insert(std::pair<int, http::connect_t> (socket_fd, connect_s(socket_fd)));
		conn = get_connect(socket_fd);
		if (!conn)
		{
			httpc::httpc_send(socket_fd, "500");
			return 1;
		}
		conn->request.connect = conn;
	}
	try {
		conn->request.content.read_socket(socket_fd);
		conn->time_req = time(NULL);
		if (conn->status == 0)
		{
			if (conn->request.parse_head(/*std::vector<ServerConfig> const &srvs_config*/))
				conn->status = 1;
			else
				return 0;
		}
		if (conn->status == 1)
		{
			if ((size_t)std::atol(conn->head.get("content-length").data()) <= conn->request.content.len())
				conn->status = 2;
			else
				return 0;	
		}
		conn->request.parse();
		http::http_send(conn);
	}
    catch (std::exception &e)
	{
		httpc::httpc_send(socket_fd, e.what());
    }
	del_connect(socket_fd);
	return 1;
}

http::connect_t*	http::get_connect(int socket_fd)
{
	std::map<int, http::connect_t>::iterator	it = _connections.find(socket_fd);

	if (it != _connections.end())
		return &(it->second);
	return NULL;
}

std::vector<http::connect_t>	http::chk_timer(time_t time_out)
{
	std::vector<http::connect_t>				res;
	std::map<int, http::connect_t>::iterator	it = _connections.begin();
	time_t										now = time(NULL);

	while (it != _connections.end())
	{
		if (now - it->second.time_req > time_out)
			res.push_back(it->second);
		it++;
	}
	return res;
}

void	http::del_connect(int socket_fd)
{
	std::map<int, http::connect_t>::iterator	it;

	it = _connections.find(socket_fd);
	if (it != _connections.end())
		_connections.erase(it);
}

void	http::get_down_to_str(std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] >= 'A' && str[i] <='Z')
			str[i] = str[i] + 32;
}
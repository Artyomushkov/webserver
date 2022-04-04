/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:08:21 by msimon            #+#    #+#             */
/*   Updated: 2022/04/02 11:12:11 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int	Request::parse_head(connect_t* conn, std::vector<ServerConfig> const &srvs_config)
{
	size_t		pos = conn->contentReq.find("\r\n\r\n");
	size_t		line_pos = 0;

	if (pos == std::string::npos)
		return 0;
	while (line_pos < pos)
	{
		if (line_pos == 0)
			parse_first_line_head(conn, conn->contentReq.get_line(line_pos));
		else
			parse_line_head(conn, conn->contentReq.get_line(line_pos));
		line_pos = conn->contentReq.find("\r\n", line_pos) + 2;
	}
	conn->contentReq.cut(0, pos + 4);
	getConfigInformation(conn, srvs_config);
	if (conn->location)
	{
		std::set<std::string>			tmp = conn->location->getHTTPmethods();
		std::set<std::string>::iterator	it = tmp.begin();
		while (it != tmp.end())
		{
			std::cout << *it << "\n";
			it++;
		}
		std::cout << conn->location->getTmpFilesDir() << "\n";
	}
	return 1;
}

void	Request::parse_first_line_head(connect_t* conn, std::string str)
{
	size_t		pos;
	std::string	uri;
	size_t		pos_get_data;

	pos = str.find(" ");
	conn->head.add("method", str.substr(0, pos));
	if (pos == std::string::npos)
		return ;
	str = str.substr(pos + 1);
	pos = str.find(" ");
	uri = str.substr(0, pos);
	pos_get_data = uri.find("?");
	conn->head.add("uri", uri.substr(0, pos_get_data));
	if (pos_get_data != std::string::npos)
		conn->get_str = uri.substr(pos_get_data + 1);
	if (pos == std::string::npos)
		return ;
	conn->head.add("http", str.substr(pos + 1));
}

void	Request::parse_line_head(connect_t* conn, std::string str)
{
	size_t				pos;

	pos = str.find(": ");
	if (pos != std::string::npos)
		conn->head.add(connect_t::down_str(str.substr(0, pos)), str.substr(pos + 2));
	else
		conn->head.add(connect_t::down_str(str.substr(0, pos)), "");
}


bool	Request::chunked_decoding(connect_t* conn)
{
	(void) conn;

	return 1;
}

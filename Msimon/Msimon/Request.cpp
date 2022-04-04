/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:08:21 by msimon            #+#    #+#             */
/*   Updated: 2022/04/04 10:19:13 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int	Request::parse_head(Connect* conn, std::vector<ServerConfig> const &srvs_config)
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
	return 1;
}

void	Request::parse_first_line_head(Connect* conn, std::string str)
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

void	Request::parse_line_head(Connect* conn, std::string str)
{
	size_t				pos;

	pos = str.find(": ");
	if (pos != std::string::npos)
		conn->head.add(Connect::down_str(str.substr(0, pos)), str.substr(pos + 2));
	else
		conn->head.add(Connect::down_str(str.substr(0, pos)), "");
}

bool	Request::chunked_decoding(Connect* conn)
{
	size_t			pos = 0;
	std::string		size_str;
	unsigned long	size;

	while (pos < conn->contentReq.len())
	{
		size_str = conn->contentReq.get_line(pos);
		size = std::strtoul(size_str.data(), NULL, 16);
		if (size == 0)
			return 1;
		conn->unChunked.push_back(conn->contentReq.get_content() + size_str.length() + 2 + pos, (size_t)size);
		pos += (size_str.length() + 4 + size);
	}
	conn->contentReq.clean();
	return 0;
}

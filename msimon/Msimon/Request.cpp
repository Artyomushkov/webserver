/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:08:21 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 17:10:52 by msimon           ###   ########.fr       */
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
//	select_server_config(conn, srvs_config);
//	анализ http заголовка и выброс исключений
	if (srvs_config.size() == 0)
		conn->config = NULL;
	return 1;
}

void	Request::parse_first_line_head(connect_t* conn, std::string str)
{
	size_t		pos;
	std::string	uri;
	size_t		pos_get_data;

	pos = str.find(" ");
	conn->dataReq.add("method", str.substr(0, pos));
	if (pos == std::string::npos)
		return ;
	str = str.substr(pos + 1);
	pos = str.find(" ");
	uri = str.substr(0, pos);
	pos_get_data = uri.find("?");
	conn->dataReq.add("uri", uri.substr(0, pos_get_data));
	if (pos_get_data != std::string::npos)
		conn->dataReq.add("get_data", uri.substr(pos_get_data + 1));
	if (pos == std::string::npos)
		return ;
	conn->dataReq.add("http", str.substr(pos + 1));
}

void	Request::get_down_to_str(std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] >= 'A' && str[i] <='Z')
			str[i] = str[i] + 32;
}

void	Request::parse_line_head(connect_t* conn, std::string str)
{
	std::string			name;
	size_t				pos;

	pos = str.find(": ");
	name = str.substr(0, pos);
	get_down_to_str(name);
	if (pos != std::string::npos)
		conn->dataReq.add(name, str.substr(pos + 2));
	else
		conn->dataReq.add(name, "");
}

//Разобрать тело записать файлы и переменные (если есть)
void	Request::parse(connect_t* conn)
{
	conn->dataReq.print();
	std::cout << "GET VAR: " << conn->dataReq.get("get_data") << "\n";
	std::cout << "HTTP BODY: ";
	conn->contentReq.print();
	std::cout << "###\n";	
	//
}
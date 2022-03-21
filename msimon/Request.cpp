/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:08:21 by msimon            #+#    #+#             */
/*   Updated: 2022/03/21 15:58:04 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int		Request::parse_head(/*std::vector<ServerConfig> const &srvs_config*/)
{
	size_t		pos = content.find("\r\n\r\n");
	size_t		line_pos = 0;

	if (pos == std::string::npos)
		return 0;
	while (line_pos < pos)
	{
		if (line_pos == 0)
			parse_first_line_head(content.get_line(line_pos));
		else
			parse_line_head(content.get_line(line_pos));
		line_pos = content.find("\r\n", line_pos) + 2;
	}
	content.cut(0, pos + 4);
//	select_server_config(response, srvs_config);
	return 1;
}

void	Request::parse_first_line_head(std::string str)
{
	size_t		pos;
	std::string	uri;
	size_t		pos_get_data;
	http::connect_t*	conn = (http::connect_t*)this->connect;

	pos = str.find(" ");
	conn->head.add("method", str.substr(0, pos));
	if (pos == std::string::npos)
		return ;
	pos = str.find(" ", pos + 1);
	uri = str.substr(0, pos);
	pos_get_data = uri.find("?");
	conn->head.add("uri", uri.substr(0, pos_get_data));
	if (pos_get_data != std::string::npos)
		conn->get_vars = uri.substr(pos_get_data + 1);
	if (pos == std::string::npos)
		return ;
	conn->head.add("http", str.substr(pos + 1));
}

void	Request::parse_line_head(std::string str)
{
	http::connect_t*	conn = (http::connect_t*)this->connect;
	std::string			name;
	size_t				pos;

	pos = str.find(": ");
	name = str.substr(0, pos);
	http::get_down_to_str(name);
	if (pos != std::string::npos)
		conn->head.add(name, str.substr(pos + 2));
	else
		conn->head.add(name, "");
}

//Разобрать тело записать файлы и переменные (если есть)
void	Request::parse()
{
	//
}
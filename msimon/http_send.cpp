/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:03:01 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 15:06:46 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

std::string getType(std::string path) //Доделать функцию
{
	size_t      pos = path.find(".");
	size_t      i;
	std::string ext;

	if (pos == std::string::npos)
		return ("");
	while (1)
	{
		i = path.find(".", pos + 1);
		if (i != std::string::npos)
			pos = i;
		else
			break;
	}
	ext = path.substr(pos + 1);
	if (ext == "html")
		return "text/html; charset=UTF-8";
	else if (ext == "jpg" || ext == "jpeg" || ext == "ico")
		return "image/" + ext;
	return "";
}

void	http::http_send(connect_t* conn)
{
	std::string	head;
	Content		content;
	
	content.read_file("." + conn->head.get("uri"));
	head = "HTTP/1.1 200 " + http::getTextCode("200") + "\r\n";
	head += "SERVER_NAME";
	head += "Connection: keep-alive\r\n";
	head += "Content-Type: " + getType(conn->head.get("uri")) + "\r\n";
	if (content.len())
		head += "Content-Length: " + std::to_string(content.len()) + "\r\n";
	head +="\r\n";

	send(conn->socket_fd, head.data(), head.length(), 0);
	if (content.len())
		send(conn->socket_fd, content.get_content(), content.len(), 0);
	send(conn->socket_fd, "\0" , 1 , 0);
}

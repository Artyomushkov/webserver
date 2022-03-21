/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http_send.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:03:01 by msimon            #+#    #+#             */
/*   Updated: 2022/03/21 14:11:03 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

void	http::http_send(connect_t* conn)
{
	std::string	content = std::string("HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<h2>HELLO</h2>");
	send(conn->socket_fd, content.data(), content.length(), 0);
	send(conn->socket_fd, "\0", 1, 0);
}

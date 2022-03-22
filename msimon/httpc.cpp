/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpc.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 12:07:49 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 15:32:36 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "httpc.hpp"

void	httpc::httpc_send(int fd, std::string code)
{
	http::connect_t*	conn = http::get_connect(fd);

	std::string	content = std::string("HTTP/1.1 ") + code + std::string(" ") + http::getTextCode(code) + std::string("\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<h2>ERROR</h2>");
	send(conn->socket_fd, content.data(), content.length(), 0);
	send(conn->socket_fd, "\0", 1, 0);
	http::del_connect(fd);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentSocket.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:39:32 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 10:45:45 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ContentSocket.hpp"

void	ContentSocket::read(int fd)
{
	char	buffer[BUFFER_SIZE_CONTENTSOCKET_HPP];
	ssize_t	read_len;

	read_len = recv(fd, buffer, BUFFER_SIZE_CONTENTSOCKET_HPP, 0);
	if (read_len < 0)
		throw (std::runtime_error("500"));
	while (read_len == BUFFER_SIZE_CONTENTSOCKET_HPP)
	{
		this->push_back(buffer, read_len);
		read_len = recv(fd , buffer, BUFFER_SIZE_CONTENTSOCKET_HPP, 0);
		if (read_len < 0)
			throw (std::runtime_error("500"));
	}
	this->push_back(buffer, read_len);
}

std::string		ContentSocket::get_line(size_t pos)
{
	std::string	res;
	size_t		f_pos = find("\r\n", pos);

	if (f_pos == std::string::npos)
	{
		if (_len < pos)
			return std::string("");
		return std::string(_content + pos, _len - pos);
	}
	else
		return std::string(_content + pos, f_pos - pos);
}

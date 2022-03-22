/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Content.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:28:33 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 12:16:00 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Content.hpp"

Content::~Content()
{
	if (_content)
		delete[] _content;
}

//		void			read_cgi();

int	Content::read_socket_add(char* buffer, ssize_t read_len)
{
	char*	n_content;

	try {n_content = new char[_len + read_len];}
	catch (std::exception &e) {return 0;}
	std::memcpy(n_content, _content, _len);
	std::memcpy(n_content + _len, buffer, read_len);
	if (_content)
		delete[] _content;
	_len += read_len;
	_content = n_content;
	return 1;
}

void	Content::read_socket(int fd)
{
	char	buffer[BUFFER_SIZE];
	ssize_t	read_len;

	read_len = recv(fd, buffer, BUFFER_SIZE, 0);
	if (read_len < 0)
		throw (std::runtime_error("500"));
	while (read_len == BUFFER_SIZE)
	{
		if (read_socket_add(buffer, read_len) == 0)
			throw (std::runtime_error("500"));
		read_len = recv(fd , buffer, BUFFER_SIZE, 0);
		if (read_len < 0)
			throw (std::runtime_error("500"));
	}
	if (read_socket_add(buffer, read_len) == 0)
		throw (std::runtime_error("500"));
}

void	Content::read_file(std::string const &path)
{
	struct stat			buf;
	std::ifstream		file;

	if (!stat(path.data(), &buf))
	{
		file.open(path.data());
		if (file.is_open())
		{
			if (_content)
			{
				delete[] _content;
				_len = 0;
				_content = NULL;
			}
			try {_content = new char[buf.st_size];}
			catch (std::exception &e)
			{
				_content = NULL;
				file.close();
				throw (std::runtime_error("500"));
			}
			file.read(_content, buf.st_size);
			_len = buf.st_size;
			file.close();
		}
		else
			throw (std::runtime_error("403"));
	}
	else
		throw (std::runtime_error("403"));
}

size_t Content::find(std::string const& str, size_t beg)
{
	if (_len < str.length())
		return std::string::npos;

	for (size_t i = beg; i <= _len - str.length(); i++)
		if (!std::memcmp(_content + i, str.data(), str.length()))
			return i;
	return std::string::npos;
}

std::string	Content::get_line(size_t pos)
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

void	Content::cut(size_t beg, size_t end)
{
	if (end > _len)
		end = _len;
	if (end <= beg)
		return ;
	if (end - beg == _len)
	{
		delete[] _content;
		_content = NULL;
		_len = 0;
		return ;
	}
	char*	n_content;

	try {n_content = new char[_len - (end - beg)];}
	catch (std::exception &e) {throw (std::runtime_error("500"));}
	std::memcpy(n_content, _content, beg);
	std::memcpy(n_content + beg, _content + end, _len - end);
	delete[] _content;
	_len = _len - (end - beg);
	_content = n_content;
}

void	Content::clean()
{
	if (_content)
		delete[] _content;
	_content = NULL;
	_len = 0;
}

void	Content::print()
{
	for (size_t i = 0; i < _len; i++)
		std::cout << _content[i];
}
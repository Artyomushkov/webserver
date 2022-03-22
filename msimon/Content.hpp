/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Content.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 18:05:58 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 11:33:21 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTENT_HPP
# define CONTENT_HPP

# include <sys/socket.h>
# include <sys/stat.h>
# include <iostream>
# include <string>
# include <cstring>
# include <fstream>

# define BUFFER_SIZE 10240

class	Content
{
	public:
		Content(): _content(NULL), _len(0) {};
		~Content();
		char*			get_content() {return _content;};
		void			read_socket(int fd);
		void			read_file(std::string const &path);
//		void			read_cgi();
		size_t 			find(std::string const& str, size_t beg = 0);
		std::string		get_line(size_t pos);
		void			cut(size_t beg, size_t end);
		void			clean();
		void			print();
		size_t const&	len() {return _len;};

	private:
//		Content(Content const &obj);
//		Content	&operator=(Content const &obj);
		char*	_content;
		size_t	_len;
		int		read_socket_add(char* buffer, ssize_t read_len);
};

#endif
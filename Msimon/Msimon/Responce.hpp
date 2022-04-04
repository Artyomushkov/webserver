/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:14:46 by msimon            #+#    #+#             */
/*   Updated: 2022/04/04 16:18:43 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_RESPONCE_HPP
# define WEBSERV_RESPONCE_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <dirent.h>
# include <fstream>
# include <string>
# include <cstdio>
# include <map>
# include <exception>
# include <cstdlib>
# include "Connect.hpp"
# include "ContentFile.hpp"
# include "HandlerCGI.hpp"

# define SERVER_NAME "JUM webserv/0.0.1"

class	Responce
{
	public:
		Responce();
		~Responce() {};
		void	sending(Connect* conn);
		void	sending(Connect* conn, std::string const& http_code, bool f_body = 1);

	private:
		std::map<std::string, std::string>	_code_error_text;
		std::map<std::string, std::string>	_mime_list;
		std::string							getExtension(std::string const& path);
		std::string							getType(std::string const& path);
		void								loadFile(Connect* conn);
		void								deleteFile(Connect* conn);
		void								send_directories(Connect* conn);
};

#endif
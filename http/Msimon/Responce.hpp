/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:14:46 by msimon            #+#    #+#             */
/*   Updated: 2022/03/26 09:25:09 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_RESPONCE_HPP
# define WEBSERV_RESPONCE_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <string>
# include <map>
# include <exception>
# include "Connect.hpp"
# include "Content/ContentFile.hpp"

# define SERVER_NAME "JUM webserv/0.0.1"

class	Responce
{
	public:
		Responce();
		~Responce() {};
		void	sending(connect_t* conn);
		void	sending(connect_t* conn, std::string const& http_code);

	private:
		std::map<std::string, std::string>	_code_error_text;		
		std::string							getType(std::string const& path);
};

#endif
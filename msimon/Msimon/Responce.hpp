/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 12:14:46 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 21:01:46 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_RESPONCE_HPP
# define WEBSERV_RESPONCE_HPP

#include <sys/types.h>
#include <sys/socket.h>
# include <string>
# include <map>
# include "Connect.hpp"
# include "ContentFile.hpp"

class	Responce
{
	public:
		Responce();
		~Responce() {};
		void	sending(connect_t* conn);
		void	sending(connect_t* conn, std::string const& http_code);

	private:
		std::map<std::string, std::string>	_code_error_text;		
		std::string							getTextCode(std::string const& http_code);
		std::string							getType(std::string const& path);
};

#endif
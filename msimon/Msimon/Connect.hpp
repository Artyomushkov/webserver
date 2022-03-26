/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connect.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:44:34 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 21:01:21 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONNECT_HPP
# define WEBSERV_CONNECT_HPP

# include <ctime>
# include "RequestData.hpp"
# include "ServerConfig.hpp"
# include "ContentSocket.hpp"

typedef	struct connect_s {
	connect_s(int _fds): fds(_fds), timeReq(time(NULL)), statusReq(0), config(NULL) {};
	int				fds;
	time_t			timeReq;
	int				statusReq;
	ServerConfig*	config;
	ContentSocket	contentReq;
	RequestData		dataReq;
}	connect_t;

#endif
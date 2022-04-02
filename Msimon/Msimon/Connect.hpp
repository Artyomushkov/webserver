/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connect.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:44:34 by msimon            #+#    #+#             */
/*   Updated: 2022/04/02 09:28:40 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONNECT_HPP
# define WEBSERV_CONNECT_HPP

# include <ctime>
# include "RequestData.hpp"
# include "Route.hpp"
# include "ContentSocket.hpp"
# include "Content.hpp"

typedef	struct connect_s {
	connect_s(int _fds): fds(_fds), timeReq(time(NULL)), statusReq(0), location(NULL) {};
	int				fds;
	time_t			timeReq;
	int				statusReq;
	const Route*	location;
	ContentSocket	contentReq;
	Content			unChunked;
	RequestData		head;
	std::string		get_str;
}	connect_t;

#endif
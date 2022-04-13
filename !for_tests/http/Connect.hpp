/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connect.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 18:44:34 by msimon            #+#    #+#             */
/*   Updated: 2022/04/13 13:35:38 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONNECT_HPP
# define WEBSERV_CONNECT_HPP

# include <ctime>
# include "RequestData.hpp"
# include "Route.hpp"
# include "ContentSocket.hpp"
# include "Content.hpp"

class Connect {
	public:
		Connect(int _fds): fds(_fds), timeReq(time(NULL)), statusReq(0), location(NULL) {};
		~Connect() {};
		int				fds;
		time_t			timeReq;
		int				statusReq;
		const Route*	location;
		ContentSocket	buffer;
		Content			contentReq;
		RequestData		head;
		std::string		get_str;
		std::string		full_file_path;
		
		void				clean();
		static std::string	down_str(std::string str);

	private:
		Connect();
};

#endif
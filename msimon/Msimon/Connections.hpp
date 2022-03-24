/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connections.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 11:57:20 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 21:01:28 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONNECTIONS_HPP
# define WEBSERV_CONNECTIONS_HPP

# include <map>
# include <vector>
# include <cstdlib>
# include <ctime>
# include "Connect.hpp"
# include "Request.hpp"
# include "Responce.hpp"

class	Connections: public Request, public Responce
{
	public:
		Connections() {};
		~Connections() {};
		int					request(int fds, std::vector<ServerConfig> const &srvs_config);
		void				responce(int fds);
		std::vector<int>	checkTime(time_t time_out);

	private:
		std::map<int, connect_t>	_connections;
		connect_t*					getConnect(int fds);
		void						delConnect(int fds);
};

#endif
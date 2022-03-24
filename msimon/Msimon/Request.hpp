/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 08:53:28 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 21:01:34 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_REQUEST_HPP
# define WEBSERV_REQUEST_HPP

# include <string>
# include <vector>
# include "ServerConfig.hpp"
# include "Connect.hpp"

class	Request
{
	public:
		Request() {};
		~Request() {};
		int		parse_head(connect_t* conn, std::vector<ServerConfig> const &srvs_config);
		void	parse(connect_t* conn);
	
	private:
		void	get_down_to_str(std::string& str);
		void	parse_first_line_head(connect_t* conn, std::string str);
		void	parse_line_head(connect_t* conn, std::string str);
//		void	select_server_config(connect_t* conn, std::vector<ServerConfig> const &srvs_config);
};

#endif

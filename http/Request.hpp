/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 08:53:28 by msimon            #+#    #+#             */
/*   Updated: 2022/04/04 10:19:13 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_REQUEST_HPP
# define WEBSERV_REQUEST_HPP

# include <string>
# include <vector>
# include "Connect.hpp"
# include "../parser/GetServer.hpp"

class	Request: public GetServer
{
	public:
		Request() {};
		~Request() {};
		int		parse_head(Connect* conn, std::vector<ServerConfig> const &srvs_config);
		bool	chunked_decoding(Connect* conn);
	
	private:
		void		parse_first_line_head(Connect* conn, std::string str);
		void		parse_line_head(Connect* conn, std::string str);
};

#endif

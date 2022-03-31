/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 08:53:28 by msimon            #+#    #+#             */
/*   Updated: 2022/03/31 20:58:00 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_REQUEST_HPP
# define WEBSERV_REQUEST_HPP

# include <string>
# include <vector>
# include <fstream>
# include <stdlib.h>
# include <string.h>
# include "Content.hpp"
# include "ServerConfig.hpp"
# include "Connect.hpp"
# include "GetServer.hpp"

class	Request: public GetServer
{
	public:
		Request(): _tmp_name("XXXXXXXXXXXXXXXX") {};
		~Request() {};
		int		parse_head(connect_t* conn, std::vector<ServerConfig> const &srvs_config);
		void	parse(connect_t* conn);
	
	private:
		void	get_down_to_str(std::string& str);
		void	parse_first_line_head(connect_t* conn, std::string str);
		void	parse_line_head(connect_t* conn, std::string str);
		void	set_application_data(RequestData& rdata, std::string const& rdata_str, std::string const& separator = std::string("&"));
		void	set_multipart_data(connect_t* conn);
		void	set_multipart_data_part(connect_t* conn, Content& part);
		void	chunked_decoding(ContentSocket& content);
		char	_tmp_name[17];
};

#endif

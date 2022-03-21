/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 08:53:28 by msimon            #+#    #+#             */
/*   Updated: 2022/03/21 16:23:52 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include <string>
# include "http.hpp"
# include "Content.hpp"

class	Request
{
	public:
		Request() {};
		~Request() {};
		void*	connect;
		Content	content;
		int		parse_head(/*std::vector<ServerConfig> const &srvs_config*/);
		void	parse();
	
	private:
//		Request(Request const &obj);
//		Request	&operator=(Request const &obj);

		void	parse_first_line_head(std::string str);
		void	parse_line_head(std::string str);
//		void	select_server_config(Response& resp, std::vector<ServerConfig> const &configs);
};

# include "http.hpp"

#endif

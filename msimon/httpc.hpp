/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   httpc.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 10:27:31 by msimon            #+#    #+#             */
/*   Updated: 2022/03/21 15:57:13 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTPC_HPP
# define HTTPC_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <string>
# include "http.hpp"

class httpc
{
	public:
		~httpc() {};
		static void	httpc_send(int fd, std::string code);
	
	private:
		httpc();
		httpc(httpc const &obj);
		httpc	&operator=(httpc const &obj);
};

#endif
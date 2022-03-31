/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentSocket.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 10:32:39 by msimon            #+#    #+#             */
/*   Updated: 2022/03/30 16:13:14 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONTENTSOCKET_HPP
# define WEBSERV_CONTENTSOCKET_HPP

# include "AContent.hpp"

# define BUFFER_SIZE_CONTENTSOCKET_HPP 10240

class ContentSocket: public AContent
{
	public:
		virtual void	read(int fd);

	private:
		virtual void	read(std::string const &path) {(void) path;};
};

#endif
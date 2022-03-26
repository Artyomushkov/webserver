/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Content.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 19:38:04 by msimon            #+#    #+#             */
/*   Updated: 2022/03/26 07:10:19 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONTENT_HPP
# define WEBSERV_CONTENT_HPP

# include "AContent.hpp"

class Content: public AContent
{
	private:
		virtual void	read(int fd) {(void) fd;};
		virtual void	read(std::string const &path) {(void) path;};
};

#endif
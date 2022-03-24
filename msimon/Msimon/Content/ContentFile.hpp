/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ContentFile.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 11:01:03 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 21:02:45 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_CONTENTFILE_HPP
# define WEBSERV_CONTENTFILE_HPP

# include "AContent.hpp"

class ContentFile: public AContent
{
	public:
		virtual void	read(std::string const &path);

	private:
		virtual void	read(int fd) {(void) fd;};
};

#endif
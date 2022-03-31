/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilesData.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:50:18 by msimon            #+#    #+#             */
/*   Updated: 2022/03/31 21:44:38 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_FILESDATA_HPP
# define WEBSERV_FILESDATA_HPP

# include <iostream>
# include <cstdio>
# include <string>
# include <map>

class FilesData
{
	public:
		typedef struct	file_s {
			std::string	file_name;
			std::string	type;
			size_t		size;
			std::string	tmp_name;
			int			error;
		} file_t;

		FilesData() {};
		~FilesData() {};
		void	add(std::string const& name);
		void	del(std::string const& name);
		void	del_files();
		file_t*	get(std::string const& name);
		void	print();

	private:
		std::map<std::string, file_t> _data;
};

#endif
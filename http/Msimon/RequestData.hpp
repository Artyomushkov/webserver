/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RequestData.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:51:57 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 21:01:40 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_REQUESTDATA_HPP
# define WEBSERV_REQUESTDATA_HPP

# include <iostream>
# include <string>
# include <map>

class RequestData
{
	public:
		RequestData() {};
		~RequestData() {};
		void		add(std::string name, std::string val);
		std::string	get(std::string name);
		void		print();

	private:
		std::map<std::string, std::string> _data;
};

#endif
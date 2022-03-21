/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Head.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:51:57 by msimon            #+#    #+#             */
/*   Updated: 2022/03/21 16:23:39 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEAD_HPP
# define HEAD_HPP

# include <string>
# include <map>

class Head
{
	public:
		Head() {};
		~Head() {};
		void		add(std::string name, std::string val);
		std::string	get(std::string name);

	private:
//		Head(Head const &obj);
//		Head	&operator=(Head const &obj);
		std::map<std::string, std::string> _head;
};

#endif
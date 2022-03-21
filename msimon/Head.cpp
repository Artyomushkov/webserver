/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Head.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 11:58:30 by msimon            #+#    #+#             */
/*   Updated: 2022/03/21 14:49:55 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Head.hpp"

void		Head::add(std::string name, std::string val)
{
	_head.insert(std::pair<std::string, std::string> (name, val));
}

std::string	Head::get(std::string name)
{
	std::map<std::string, std::string>::iterator	it;

	it = _head.find(name);
	if (it != _head.end())
		return it->second;
	return std::string("");
}

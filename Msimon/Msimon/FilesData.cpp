/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FilesData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 17:06:47 by msimon            #+#    #+#             */
/*   Updated: 2022/03/31 21:46:57 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FilesData.hpp"

void	FilesData::add(std::string const& name)
{
	file_t*	post_file = get(name);

	if (!post_file)
		_data[name] = file_s();	
}

void	FilesData::del(std::string const& name)
{
	std::map<std::string, file_t>::iterator	it = _data.find(name);

	if (it != _data.end())
		_data.erase(it);
}

FilesData::file_t*	FilesData::get(std::string const& name)
{
	std::map<std::string, file_t>::iterator	it = _data.find(name);

	if (it != _data.end())
		return &(it->second);
	return NULL;
}

void	FilesData::print()
{
	std::map<std::string, file_t>::iterator	it = _data.begin();
	
	while (it != _data.end())
	{
		std::cout << it->first << ": File name - " << it->second.file_name << "; Type - " <<
			it->second.type << "; Size - " << std::to_string(it->second.size) << "; Temp name - " <<
			it->second.tmp_name << "; Error - " << std::to_string(it->second.error) << "\n";
		it++;
	}
}

void	FilesData::del_files()
{
	std::map<std::string, file_t>::iterator	it = _data.begin();
	
	while (it != _data.end())
	{
		if (it->second.error == 0)
			std::remove(it->second.tmp_name.data());
		it++;
	}
}
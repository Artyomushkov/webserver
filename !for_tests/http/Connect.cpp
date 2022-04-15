/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Connect.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 11:03:59 by msimon            #+#    #+#             */
/*   Updated: 2022/04/14 13:04:11 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Connect.hpp"

std::string	Connect::down_str(std::string str)
{
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] >= 'A' && str[i] <='Z')
			str[i] = str[i] + 32;
	return (str);
}

void	Connect::clean()
{
	timeReq = std::time(NULL);
	statusReq = 0;
	location = NULL;
	head.clean();
	body.clean();
	get_str = "";
	full_file_path = "";
}
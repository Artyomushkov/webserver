/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 12:01:20 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 15:28:14 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HTTP_HPP
# define HTTP_HPP

# include <sys/types.h>
# include <sys/socket.h>
# include <string>
# include <cstdlib>
# include <ctime>
# include <vector>
# include <map>
# include "httpc.hpp"
# include "Head.hpp"
# include "Request.hpp"
# include "Content.hpp"

class	http
{
	public:
		~http();
		typedef	struct connect_s {
			connect_s(int _socket_fd): socket_fd(_socket_fd), time_req(time(NULL)), status(0) {};
			int 			socket_fd;
			Request			request;
			time_t			time_req;
			int				status; //Статус соединения 0 - получени данных от клиента, 1 - получен и распарсен заголовок, выбран сервер и получение тела запроса, 2 запрос полностью получен и направлен на формирование ответа
			Head			head; // заголовок распарсенный (head.get("content-length"))
			std::string		get_vars;
			std::string		post_vars;
//			ServerConfig*	config = NULL; // конфигурация нужного сервера
//			Files			files; //файлы из тела post			
		}	connect_t;
		static void							init();
		static int							run_request(int socket_fd/*, std::vector<ServerConfig> const &srvs_config*/);
		static http::connect_t*	 			get_connect(int socket_fd);
		static void							del_connect(int socket_fd);
		static std::vector<int>				chk_timer(time_t time_out);
		static void							http_send(http::connect_t* conn);
		static std::string					getTextCode(std::string http_code);

//for string
		static void	get_down_to_str(std::string& str);
//		

	private:
		http();
		http(http const &obj);
		http	&operator=(http const &obj);

		static std::map<int, http::connect_t>		_connections;
		static std::map<std::string, std::string>	_code_error_text;
};

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   http.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 07:29:49 by msimon            #+#    #+#             */
/*   Updated: 2022/03/22 16:14:08 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "http.hpp"

std::map<int, http::connect_t>	http::_connections;
std::map<std::string, std::string>	http::_code_error_text;

int	http::run_request(int socket_fd/*, std::vector<ServerConfig> const &srvs_config*/)
{
	http::connect_t*	conn = get_connect(socket_fd);

	if (!conn)
	{
		_connections.insert(std::pair<int, http::connect_t> (socket_fd, connect_s(socket_fd)));
		conn = get_connect(socket_fd);
		if (!conn)
		{
			httpc::httpc_send(socket_fd, "500");
			return 1;
		}
		conn->request.connect = conn;
	}
	try {
		conn->request.content.read_socket(socket_fd);
		conn->time_req = time(NULL);
		if (conn->status == 0)
		{
			if (conn->request.parse_head(/*std::vector<ServerConfig> const &srvs_config*/))
				conn->status = 1;
			else
				return 0;
		}
		if (conn->status == 1)
		{
			if ((size_t)std::atol(conn->head.get("content-length").data()) <= conn->request.content.len())
				conn->status = 2;
			else
				return 0;	
		}
		conn->request.parse();
		http::http_send(conn);
	}
    catch (std::exception &e)
	{
		httpc::httpc_send(socket_fd, e.what());
    }
	del_connect(socket_fd);
	return 1;
}

http::connect_t*	http::get_connect(int socket_fd)
{
	std::map<int, http::connect_t>::iterator	it = _connections.find(socket_fd);

	if (it != _connections.end())
		return &(it->second);
	return NULL;
}

std::vector<int>	http::chk_timer(time_t time_out)
{
	std::vector<int>				res;
	std::map<int, http::connect_t>::iterator	it = _connections.begin();
	time_t										now = time(NULL);

	while (it != _connections.end())
	{
		if (now - it->second.time_req > time_out)
			res.push_back(it->first);
		it++;
	}
	return res;
}

void	http::del_connect(int socket_fd)
{
	std::map<int, http::connect_t>::iterator	it;

	it = _connections.find(socket_fd);
	if (it != _connections.end())
		_connections.erase(it);
}

void	http::get_down_to_str(std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] >= 'A' && str[i] <='Z')
			str[i] = str[i] + 32;
}

void	http::init()
{
	_code_error_text["100"] = "Continue";
	_code_error_text["101"] = "Switching Protocol";
	_code_error_text["102"] = "Processing";
	_code_error_text["103"] = "Early Hints";
	_code_error_text["200"] = "OK";
	_code_error_text["201"] = "Created";
	_code_error_text["202"] = "Accepted";
	_code_error_text["203"] = "Non-Authoritative Information";
	_code_error_text["204"] = "No Content";
	_code_error_text["205"] = "Reset Content";
	_code_error_text["206"] = "Partial Content";
	_code_error_text["300"] = "Multiple Choice";
	_code_error_text["301"] = "Moved Permanently";
	_code_error_text["302"] = "Found";
	_code_error_text["303"] = "See Other";
	_code_error_text["304"] = "Not Modified";
	_code_error_text["305"] = "Use Proxy";
	_code_error_text["306"] = "Switch Proxy";
	_code_error_text["307"] = "Temporary Redirect";
	_code_error_text["308"] = "Permanent Redirect";
	_code_error_text["400"] = "Bad Request";
	_code_error_text["401"] = "Unauthorized";
	_code_error_text["402"] = "Payment Required";
	_code_error_text["403"] = "Forbidden";
	_code_error_text["404"] = " Not Found";
	_code_error_text["405"] = "Method Not Allowed";
	_code_error_text["406"] = "Not Acceptable";
	_code_error_text["407"] = "Proxy Authentication Required";
	_code_error_text["408"] = "Request Timeout";
	_code_error_text["409"] = "Conflict";
	_code_error_text["410"] = "Gone";
	_code_error_text["411"] = "Length Required";
	_code_error_text["412"] = "Precondition Failed";
	_code_error_text["413"] = "Request Entity Too Large";
	_code_error_text["414"] = "Request-URI Too Long";
	_code_error_text["415"] = "Unsupported Media Type";
	_code_error_text["416"] = "Requested Range Not Satisfiable";
	_code_error_text["417"] = "Expectation Failed";
	_code_error_text["500"] = "Internal Server Error";
	_code_error_text["501"] = "Not Implemented";
	_code_error_text["502"] = "Bad Gateway";
	_code_error_text["503"] = "Service Unavailable";
	_code_error_text["504"] = "Gateway Timeout";
	_code_error_text["505"] = "HTTP Version Not Supported";
}

std::string	http::getTextCode(std::string http_code)
{
	std::map<std::string, std::string>::iterator	it = _code_error_text.find(http_code);

	if (it != _code_error_text.end())
		return it->second;
	return ("");
}
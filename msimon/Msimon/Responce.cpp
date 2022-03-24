/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:04:37 by msimon            #+#    #+#             */
/*   Updated: 2022/03/24 17:03:50 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responce.hpp"

Responce::Responce()
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

std::string	Responce::getTextCode(std::string const& http_code)
{
	std::map<std::string, std::string>::iterator	it = _code_error_text.find(http_code);

	if (it != _code_error_text.end())
		return it->second;
	return ("");
}

std::string	Responce::getType(std::string const& path)
{
	size_t		pos = path.find(".");
	size_t		i;
	std::string	ext;

	if (pos == std::string::npos)
		return ("");
	while (1)
	{
		i = path.find(".", pos + 1);
		if (i != std::string::npos)
			pos = i;
		else
			break;
	}
	ext = path.substr(pos + 1);
	if (ext == "html")
		return "text/html; charset=UTF-8";
	else if (ext == "jpg" || ext == "jpeg" || ext == "ico")
		return "image/" + ext;
	return "";
}

void	Responce::sending(connect_t* conn)
{
	std::string	head;
	ContentFile	content;
	
	content.read("." + conn->dataReq.get("uri"));
	head = "HTTP/1.1 200 " + getTextCode("200") + "\r\n";
	head += "SERVER_NAME";
	head += "Connection: keep-alive\r\n";
	head += "Content-Type: " + getType(conn->dataReq.get("uri")) + "\r\n";
	if (content.len())
		head += "Content-Length: " + std::to_string(content.len()) + "\r\n";
	head +="\r\n";

	send(conn->fds, head.data(), head.length(), 0);
	if (content.len())
		send(conn->fds, content.get_content(), content.len(), 0);
	send(conn->fds, "\0" , 1 , 0);
}

void	Responce::sending(connect_t* conn, std::string const& http_code)
{
	std::string	content = std::string("HTTP/1.1 ") + http_code + std::string(" ") + getTextCode(http_code) + std::string("\r\nContent-Type: text/html; charset=UTF-8\r\n\r\n<h2>ERROR</h2>");
	send(conn->fds, content.data(), content.length(), 0);
	send(conn->fds, "\0", 1, 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:04:37 by msimon            #+#    #+#             */
/*   Updated: 2022/04/04 16:33:28 by msimon           ###   ########.fr       */
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
	_code_error_text["508"] = "Loop Detected";
	_mime_list["aac"] = "audio/aac";
	_mime_list["abw"] = "application/x-abiword";
	_mime_list["arc"] = "application/x-freearc";
	_mime_list["avi"] = "video/x-msvideo";
	_mime_list["azw"] = "application/vnd.amazon.ebook";
	_mime_list["bin"] = "application/octet-stream";
	_mime_list["bmp"] = "image/bmp";
	_mime_list["bz"] = "application/x-bzip";
	_mime_list["bz2"] = "application/x-bzip2";
	_mime_list["csh"] = "application/x-csh";
	_mime_list["css"] = "text/css; charset=UTF-8";
	_mime_list["csv"] = "text/csv; charset=UTF-8";
	_mime_list["doc"] = "application/msword";
	_mime_list["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	_mime_list["eot"] = "application/vnd.ms-fontobject";
	_mime_list["epub"] = "application/epub+zip";
	_mime_list["gz"] = "application/gzip";
	_mime_list["gif"] = "image/gif";
	_mime_list["htm"] = "text/html; charset=UTF-8";
	_mime_list["html"] = "text/html; charset=UTF-8";
	_mime_list["ico"] = "image/vnd.microsoft.icon";
	_mime_list["ics"] = "text/calendar; charset=UTF-8";
	_mime_list["jar"] = "application/java-archive";
	_mime_list["jpeg"] = "image/jpeg";
	_mime_list["jpg"] = "image/jpeg";
	_mime_list["js"] = "text/javascript; charset=UTF-8";
	_mime_list["json"] = "application/json";
	_mime_list["jsonld"] = "application/ld+json";
	_mime_list["mid"] = "audio/midi";
	_mime_list["midi"] = "audio/x-midi";
	_mime_list["mjs"] = "text/javascript; charset=UTF-8";
	_mime_list["mp3"] = "audio/mpeg";
	_mime_list["mpeg"] = "video/mpeg";
	_mime_list["mpkg"] = "application/vnd.apple.installer+xml";
	_mime_list["odp"] = "application/vnd.oasis.opendocument.presentation";
	_mime_list["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	_mime_list["odt"] = "application/vnd.oasis.opendocument.text";
	_mime_list["oga"] = "audio/ogg";
	_mime_list["ogv"] = "video/ogg";
	_mime_list["ogx"] = "application/ogg";
	_mime_list["opus"] = "audio/opus";
	_mime_list["otf"] = "font/otf";
	_mime_list["png"] = "image/png";
	_mime_list["pdf"] = "application/pdf";
	_mime_list["php"] = "application/php";
	_mime_list["ppt"] = "application/vnd.ms-powerpoint";
	_mime_list["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	_mime_list["rar"] = "application/vnd.rar";
	_mime_list["rtf"] = "application/rtf";
	_mime_list["sh"] = "application/x-sh";
	_mime_list["svg"] = "image/svg+xml";
	_mime_list["swf"] = "application/x-shockwave-flash";
	_mime_list["tar"] = "application/x-tar";
	_mime_list["tif"] = "image/tiff";
	_mime_list["tiff"] = "image/tiff";
	_mime_list["ts"] = "video/mp2t";
	_mime_list["ttf"] = "font/ttf";
	_mime_list["txt"] = "text/plain; charset=UTF-8";
	_mime_list["vsd"] = "application/vnd.visio";
	_mime_list["wav"] = "audio/wav";
	_mime_list["weba"] = "audio/webm";
	_mime_list["webm"] = "video/webm";
	_mime_list["webp"] = "image/webp";
	_mime_list["woff"] = "font/woff";
	_mime_list["woff2"] = "font/woff2";
	_mime_list["xhtml"] = "application/xhtml+xml";
	_mime_list["xls"] = "application/vnd.ms-excel";
	_mime_list["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	_mime_list["xml"] = "application/xml";
	_mime_list["xul"] = "application/vnd.mozilla.xul+xml";
	_mime_list["zip"] = "application/zip";
	_mime_list["3gp"] = "video/3gpp";
	_mime_list["3g2"] = "video/3gpp2";
	_mime_list["7z"] = "application/x-7z-compressed";	
}

std::string	Responce::getExtension(std::string const& path)
{
	size_t		pos = path.find(".");
	size_t		i;

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
	return path.substr(pos + 1);
}

std::string	Responce::getType(std::string const& path)
{
	std::string	ext = Connect::down_str(getExtension(path));
	std::map<std::string, std::string>::iterator	it;

	it = _mime_list.find(ext);
	if (it != _mime_list.end())
		return it->second;
	return "application/octet-stream";
}

void	Responce::sending(Connect* conn)
{
	std::string	file_path;
	std::string	head;
	
	if (conn->location)
	{
		if (conn->location->getRedirection() != "")
		{
			if (conn->location->getRoute() == conn->location->getRedirection())
				throw (std::runtime_error("508"));
			head = "HTTP/1.1 301 " + _code_error_text.find("301")->second + "\r\n";
			head += "Location: " + conn->location->getRedirection() + conn->head.get("uri").substr(conn->location->getRoute().length()) + "\r\n";
			head +="\r\n";
			send(conn->fds, head.data(), head.length(), 0);
			send(conn->fds, "\0" , 1 , 0);
			return ;
		}
		if (conn->location->getRoute() == conn->head.get("uri"))
		{
			std::set<std::string>			tmp_set = conn->location->getDefaultPages();
			std::set<std::string>::iterator	tmp_set_it = tmp_set.begin();
			std::ifstream		file_index;
			while (tmp_set_it != tmp_set.end())
			{
				file_path = conn->location->getRoot() + "/" + *tmp_set_it;
				file_index.open(file_path);
				if (file_index.is_open())
				{
					file_index.close();
					break;
				}
				file_index.close();
				file_path = "";
				tmp_set_it++;
			}
		}
		if (file_path == "" && conn->location->getAutoindex()
			&& conn->head.get("uri").data()[conn->head.get("uri").length() - 1] == '/')
		{
			send_directories(conn);
			return ;
		}
		if (file_path == "")
			file_path = conn->location->getRoot() + "/" + conn->head.get("uri").substr(conn->location->getRoute().length());			
		//Проверка файла по расширению на CGI
		//std::cout << Connect::down_str(getExtension(file_path)) << "\n";

		if (conn->head.get("method") == "PUT")
		{
			loadFile(conn);
			return ;
		}
		if (conn->head.get("method") == "DELETE")
		{
			deleteFile(conn);
			return ;
		}
		ContentFile	content;
		content.read(file_path);
		head = "HTTP/1.1 200 " + _code_error_text.find("200")->second + "\r\n";
		head += "Server: " + std::string(SERVER_NAME) + "\r\n";
		head += "Connection: keep-alive\r\n";
		head += "Content-Type: " + getType(file_path) + "\r\n";
		if (content.len())
			head += "Content-Length: " + std::to_string(content.len()) + "\r\n";
		head +="\r\n";
		send(conn->fds, head.data(), head.length(), 0);
		if (content.len())
			send(conn->fds, content.get_content(), content.len(), 0);
		send(conn->fds, "\0" , 1 , 0);
	}
	else
		throw (std::runtime_error("503"));
}

void	Responce::sending(Connect* conn, std::string const& http_code, bool f_body)
{
	try {
		std::map<std::string, std::string>::iterator	it = _code_error_text.find(http_code);
		if (it == _code_error_text.end() || it == _code_error_text.find("200"))		
			it = _code_error_text.find("500");

		ContentFile	errPage;
		if (conn->location)
		{
			std::map<int, std::string>				tmp = conn->location->getErrorPages();
			std::map<int, std::string>::iterator	tmp_it = tmp.find(std::atol(it->first.data()));
			if (tmp_it != tmp.end())
			{
				try {errPage.read(tmp_it->second);}
				catch (std::exception &e) {errPage.clean();}
			}
		}
		
		std::string	content;
		content = "HTTP/1.1 " + http_code + " " + it->second + "\r\n";
		if (f_body)
			content += "Content-Type: text/html; charset=UTF-8\r\n";
		content += "Connection: keep-alive\r\n";
		content += "Server: " + std::string(SERVER_NAME) + "\r\n";
		content += "\r\n";
		send(conn->fds, content.data(), content.length(), 0);
		if (f_body)
		{
			if (errPage.len())
				send(conn->fds, errPage.get_content(), errPage.len(), 0);
			else
			{
				content = "<html><head><meta charset=\"utf-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">";
				content += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>";
				content += it->first + " - " + it->second;
				content += "</title></head><body style='width: 100%;height: 100%;background-color: #21232a;margin: 0;";
				content += "line-height: 1.15;color: #fff;text-align: center;text-shadow: 0 2px 4px rgba(0,0,0,.5);padding: 0;";
				content += "min-height: 100%;-webkit-box-shadow: inset 0 0 100px rgba(0,0,0,.8);box-shadow: inset 0 0 100px rgba(0,0,0,.8);";
				content += "display: table;font-family: \"Open Sans\",Arial,sans-serif;text-align: center;text-shadow: 0 2px 4px rgba(0,0,0,.5);'>";
				content += "<div style='display: table-cell;vertical-align: middle;padding: 0 20px;'><h1 style='font-family: inherit;font-weight: 500;";
				content += "line-height: 1.1;color: inherit;font-size: 36px;'>";
				content += it->second;
				content += "&nbsp;<small style='font-size: 150%;font-weight: 400;line-height: 1;color: #777;'>";
				content += it->first;
				content += "</small></h1></div></body></html>";
				send(conn->fds, content.data(), content.length(), 0);
			}
		}
		if (f_body)
			send(conn->fds, "\0", 1, 0);
	}
	catch (std::exception &e) {
		std::cerr << "failed to send error to client\n";
	}
}

void	Responce::loadFile(Connect* conn)
{
	std::string		path = conn->location->getUploadDirectory()
		+ "/" + conn->head.get("uri").substr(conn->location->getRoute().length());
	std::ifstream	found_file;
	bool			f_file = 0;
	std::ofstream	put_file;

	found_file.open(path);
	if (found_file.is_open())
		f_file = 1;
	found_file.close();
	put_file.open(path);
	if (put_file.is_open())
	{
		if (conn->unChunked.len())
			put_file.write(conn->unChunked.get_content(), conn->unChunked.len());
		else
			put_file.write(conn->contentReq.get_content(), conn->contentReq.len());
		put_file.close();
		if (f_file)
			sending(conn, "204", 0);
		else
			sending(conn, "201", 0);
	}
	else
	{
		put_file.close();
		throw (std::runtime_error("412"));
	}
}

void	Responce::deleteFile(Connect* conn)
{
	std::string		path = conn->location->getUploadDirectory()
		+ "/" + conn->head.get("uri").substr(conn->location->getRoute().length());
	std::ifstream	found_file;

	found_file.open(path);
	if (found_file.is_open())
	{
		found_file.close();
		std::remove(path.data());
		sending(conn, "204", 0);
	}
	else
	{
		found_file.close();
		throw (std::runtime_error("412"));
	}
}

void	Responce::send_directories(Connect* conn)
{
	std::string		path = conn->location->getRoot()
		+ "/" + conn->head.get("uri").substr(conn->location->getRoute().length());
	DIR				*p_dir;
	struct dirent	*dir_el;

	p_dir = opendir(path.data());
	if (p_dir)
	{
		dir_el = readdir(p_dir);
		while (dir_el)
		{
			std::cout << std::string(dir_el->d_name) << "\n";
			dir_el = readdir(p_dir);
		}
		closedir(p_dir);
	}
}
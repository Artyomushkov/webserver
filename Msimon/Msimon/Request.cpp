/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/20 09:08:21 by msimon            #+#    #+#             */
/*   Updated: 2022/03/31 21:20:54 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Request.hpp"

int	Request::parse_head(connect_t* conn, std::vector<ServerConfig> const &srvs_config)
{
	size_t		pos = conn->contentReq.find("\r\n\r\n");
	size_t		line_pos = 0;

	if (pos == std::string::npos)
		return 0;
	while (line_pos < pos)
	{
		if (line_pos == 0)
			parse_first_line_head(conn, conn->contentReq.get_line(line_pos));
		else
			parse_line_head(conn, conn->contentReq.get_line(line_pos));
		line_pos = conn->contentReq.find("\r\n", line_pos) + 2;
	}
	conn->contentReq.cut(0, pos + 4);
	getConfigInformation(conn, srvs_config);
	if (conn->location)
	{
		std::set<std::string>			tmp = conn->location->getHTTPmethods();
		std::set<std::string>::iterator	it = tmp.begin();
		while (it != tmp.end())
		{
			std::cout << *it << "\n";
			it++;
		}
		std::cout << conn->location->getTmpFilesDir() << "\n";
	}
	return 1;
}

void	Request::parse_first_line_head(connect_t* conn, std::string str)
{
	size_t		pos;
	std::string	uri;
	size_t		pos_get_data;

	pos = str.find(" ");
	conn->head.add("method", str.substr(0, pos));
	if (pos == std::string::npos)
		return ;
	str = str.substr(pos + 1);
	pos = str.find(" ");
	uri = str.substr(0, pos);
	pos_get_data = uri.find("?");
	conn->head.add("uri", uri.substr(0, pos_get_data));
	if (pos_get_data != std::string::npos)
		set_application_data(conn->get, uri.substr(pos_get_data + 1));
	if (pos == std::string::npos)
		return ;
	conn->head.add("http", str.substr(pos + 1));
}

void	Request::get_down_to_str(std::string& str)
{
	for (size_t i = 0; i < str.length(); i++)
		if (str[i] >= 'A' && str[i] <='Z')
			str[i] = str[i] + 32;
}

void	Request::parse_line_head(connect_t* conn, std::string str)
{
	std::string			name;
	size_t				pos;

	pos = str.find(": ");
	name = str.substr(0, pos);
	get_down_to_str(name);
	if (pos != std::string::npos)
		conn->head.add(name, str.substr(pos + 2));
	else
		conn->head.add(name, "");
}

void	Request::parse(connect_t* conn)
{
	if (conn->head.get("transfer-encoding") == "chunked")
		chunked_decoding(conn->contentReq);
	if (conn->head.get("method") == "POST")
	{
		std::string	content_type = conn->head.get("content-type");
		if (content_type == "text/plain")
			set_application_data(conn->post, std::string(conn->contentReq.get_content(), conn->contentReq.len()), std::string("\r\n"));
		else if (content_type.find("multipart/form-data") != std::string::npos)
			set_multipart_data(conn);
		else
			set_application_data(conn->post, std::string(conn->contentReq.get_content(), conn->contentReq.len()));
	}

	std::cout << "###\n";
	conn->head.print();
	conn->get.print();
	conn->post.print();
	conn->files.print();
	std::cout << "###\n";	
}

void	Request::set_application_data(RequestData& rdata, std::string const& rdata_str, std::string const& separator)
{
	if (rdata_str != "")
	{
		std::string	val_str;
		size_t		pos;
		size_t		beg = 0;
		size_t		end = rdata_str.find(separator);
		while (end != std::string::npos)
		{
			val_str = rdata_str.substr(beg, end - beg);
			pos = val_str.find('=');
			if (pos != std::string::npos)
				rdata.add(val_str.substr(0, pos), val_str.substr(pos + 1));
			beg = end + separator.length();
			end = rdata_str.find(separator, beg);
		}
		val_str = rdata_str.substr(beg, end - beg);
		pos = val_str.find('=');
		if (pos != std::string::npos)
			rdata.add(val_str.substr(0, pos), val_str.substr(pos + 1));
	}
}

void	Request::set_multipart_data(connect_t* conn)
{
	Content		buf;
	size_t		beg;
	size_t		end;
	std::string	separator = conn->head.get("content-type");

	separator = "--" + separator.substr(separator.find("boundary=") + 9) + "\r\n";
	beg = separator.length();
	end = conn->contentReq.find(separator, beg);
	while (end != std::string::npos)
	{
		buf.clean();
		buf.push_back(conn->contentReq.get_content() + beg, end - beg - 2);
		set_multipart_data_part(conn, buf);
		beg = end + separator.length();
		end = conn->contentReq.find(separator, beg);
	}
	buf.clean();
	buf.push_back(conn->contentReq.get_content() + beg, conn->contentReq.len() - separator.length() - beg - 4);
	set_multipart_data_part(conn, buf);
}

void	Request::set_multipart_data_part(connect_t* conn, Content& part)
{
	size_t		pos = 0;
	size_t		beg;
	size_t		end;
	int			file_flag = 0;
	std::string	str;
	std::string	name;
	std::string	file_name;
	std::string	file_type;
	
	while ((str = part.get_line(pos)) != "")
	{
		if (str.find("Content-Disposition:") == 0)
		{
			if ((beg = str.find("name=\"")) != std::string::npos)
			{
				beg += 6;
				end = str.find("\"", beg);
				name = str.substr(beg, end - beg);
			}
			if ((beg = str.find("filename=\"")) != std::string::npos)
			{
				file_flag = 1;
				beg += 10;
				end = str.find("\"", beg);
				file_name = str.substr(beg, end - beg);				
			}
		}
		if (str.find("Content-Type: ") == 0)
			file_type = str.substr(14);
		pos += str.length() + 2;
	}
	part.cut(0, pos + 2);
	if (file_flag)
	{
		conn->files.add(name);
		FilesData::file_t*	fld = conn->files.get(name);
		fld->file_name = file_name;
		fld->type = file_type;
		fld->size = part.len();
		memset(_tmp_name, 'X', 16);
		mktemp(_tmp_name);
		fld->tmp_name = "./tmp/" + std::string(_tmp_name); //заменить на данные из конфига
		std::ofstream	ofs(fld->tmp_name);
		if (ofs.is_open())
		{
			ofs.write(part.get_content(), fld->size);
			fld->error = 0;
			ofs.close();
		}
		else
			fld->error = 1;		
	}
	else
		conn->post.add(name, std::string(part.get_content(), part.len()));
}

void	Request::chunked_decoding(ContentSocket& content)
{
	(void) content;
	//asd
}
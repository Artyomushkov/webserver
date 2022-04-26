#ifndef WEBSERV_COOKIE_H
#define WEBSERV_COOKIE_H
#include "string"
#include <vector>
#include <ctime>
#include <algorithm>
#include "Session.hpp"

class Cookie
{
	Session _session;
	std::vector<int> session_ids;
	bool has_session_id(std::string);

	std::string get_time(int);

public:
	Cookie() {
		session_ids.push_back(1);
	}
	std::string get_cookie_string(std::string);
//	std::string delete_cookie_string();
};

#endif //WEBSERV_COOKIE_H
//server/RequestHandler.cpp
//		server/ServerManager.cpp
//		server/Socket.cpp
//		parser/ConfigParser.cpp
//		parser/GetServer.cpp
//		parser/Route.cpp
//		parser/ServerConfig.cpp
//		parser/utils.cpp
//		http/Content/AContent.cpp
//		http/Content/ContentFile.cpp
//		http/Content/ContentSocket.cpp
//		http/Connect.cpp
//		http/Connections.cpp
//		http/Request.cpp
//		http/RequestData.cpp
//		http/Responce.cpp
//		cgi/HandlerCGI.cpp
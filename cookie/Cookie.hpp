#ifndef WEBSERV_COOKIE_H
#define WEBSERV_COOKIE_H
#include "string"

class Cookie
{
	std::string name;
	std::string value;
	std::string expires; // время хранения
	std::string max_age;
	std::string domain;
	std::string secure;
	std::string httponly;
	std::string samesite;

public:
	Cookie(std::string name, std::string value, std::string expires);
	Cookie(std::string name, std::string value);
	std::string set_cookie_string();
	std::string delete_cookie_string();
};


#endif //WEBSERV_COOKIE_H

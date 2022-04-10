#include "Cookie.hpp"

std::string Cookie::get_time(int t)
{
	char       time_str[100];
	time_t curr_time = time(NULL);
	time_t time = curr_time + t;
	strftime(time_str, 100, "%a, %d %b %Y %H:%M:%S GMT", gmtime
			(&time));
	return time_str;
}

Cookie::Cookie(std::string name, std::string value)
{
	//Cookie: NAME1=OPAQUE_STRING1; NAME2=OPAQUE_STRING2
	this->name = name;
	this->value = value;
}
std::string Cookie::set_cookie_string()
{
	std::string cookie_string = "Set-Cookie: "+ name + "=" + value + ";";
	return cookie_string;
}
std::string Cookie::delete_cookie_string()
{
	std::string cookie_string = "Set-Cookie: "+ name + "=" + value + "=; "
																	 "expires=" +
			get_time(-3600);
	return cookie_string;
}
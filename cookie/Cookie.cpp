#include "Cookie.hpp"

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
	std::string cookie_string = "Set-Cookie: "+ name + "=" + value + "=; expires=" +  ;
	return cookie_string;
}
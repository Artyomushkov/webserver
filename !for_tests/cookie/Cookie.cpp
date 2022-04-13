#include "Cookie.hpp"

std::string Cookie::get_time(int t)
{
	char       time_str[100];
	time_t curr_time = std::time(NULL);
	time_t time = curr_time + t;
	std::strftime(time_str, 100, "%a, %d %b %Y %H:%M:%S GMT", std::gmtime
			(&time));
	return time_str;
}

bool Cookie::has_session_id(std::string header)
{
	std::string id = "";
	size_t i = header.find("session_id");
	if (i != std::string::npos)
	{
		i += 11;
		while(header[i] != ';')
			id = id + header[i++];
		if(find(session_ids.begin(), session_ids.end(), stoi(id)) !=
		session_ids.end())
			return true;
	}
	return false;
}

std::string Cookie::get_cookie_string(std::string header)
{
	std::string cookie_string = "";

	if (!has_session_id(header))
	{
		int id = _session.get_sessionid();
		cookie_string = cookie_string + "session_id" + "=" + std::to_string(id) + ";";
		session_ids.push_back(id);
	}
	if (header.find("name") == std::string::npos)
		cookie_string = cookie_string + "name" + "=" + "Cookie_name; Expires=" +
													   get_time(3600) +";";
	return cookie_string;
}

//std::string Cookie::delete_cookie_string()
//{
//	std::string cookie_string = "Set-Cookie: "+ name + "=" + value + "=; "
//																	 "expires=" +
//			get_time(-3600);
//	return cookie_string;
//}
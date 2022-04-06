//
// Created by urichese on 05.04.2022.
//

#ifndef WEBSERV_SESSION_H
#define WEBSERV_SESSION_H
#include "string"
#include <time.h>

class Session
{
	int sessionid;
public:
	int get_sessionid();
	void generate_id();
};


#endif //WEBSERV_SESSION_H

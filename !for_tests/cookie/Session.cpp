//
// Created by urichese on 05.04.2022.
//

#include "Session.hpp"

void Session::generate_id()
{
	sessionid = 1 + rand()%(100000);
}

int Session::get_sessionid()
{
	generate_id();
	return sessionid;
}

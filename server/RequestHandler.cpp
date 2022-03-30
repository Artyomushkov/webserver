//
// Created by Uncle Richese on 3/15/22.
//

#include "RequestHandler.hpp"

RequestHandler::RequestHandler()
{

}

int RequestHandler::get(int fd, std::vector<ServerConfig> servers)
{
	std::cout << "------------------------" << std::endl;
	std::cout << fd << std::endl;
	std::cout << "------------------------" << std::endl;
	for(std::vector<ServerConfig>::iterator it = servers.begin();
		it != servers.end();
		++it)
	{
		std::cout << "------------------------" << std::endl;
	}
	std::cout << "------------------------" << std::endl;
	return fd;
}

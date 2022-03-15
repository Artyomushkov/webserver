#ifndef WEBSERV_SERVERCONFIG_HPP
#define WEBSERV_SERVERCONFIG_HPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <utility>
#include "Route.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>
#include <cstdlib>
#include "utils.hpp"

class ServerConfig {

private:
	std::vector<std::pair<in_addr_t, int> >			_request_address; //map
	std::set<std::string>							_server_names;
	std::map<int, std::string>						_error_pages;
	std::set<std::string>							_default_pages;
	std::string										_root;
	int 											_limit_body_size;
	std::vector<Route>								_routes;

public:
	ServerConfig();
	~ServerConfig();
	void	parseServer(std::ifstream& file);
	void showInfo() const;

	const std::vector<std::pair<in_addr_t, int> >& getVectorOfAddresses() const;
	const std::set<std::string>& getServerNames() const;
	const std::map<int, std::string>& getErrorPages() const;
	const std::set<std::string>& getDefaultPages() const;
	const std::string& getRootOfServer() const;
	int getBodySizeLimit() const;
	const std::vector<Route>& getServerRoutes() const;


private:
	void fill_errors();
	void parseRequestAddress(std::vector<std::string>& command);
	void parseServerNames(std::vector<std::string>& command);
	void parseErrorPages(std::vector<std::string>& command);
	void parseClientMaxBodySize(std::vector<std::string>& command);
	void parseRoot(std::vector<std::string>& command);
	void parseIndex(std::vector<std::string>& command);
	void parseRoutePreporation(std::ifstream& file,
							   std::vector<std::string>& command);
	bool ifIPvalid(std::string& ip_address);
};


#endif

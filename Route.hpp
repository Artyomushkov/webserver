#ifndef WEBSERV_ROUTES_HPP
#define WEBSERV_ROUTES_HPP

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
#include "utils.hpp"

class Route {

private:
	std::string				_route;
	std::set<std::string>	_default_pages;
	std::set<std::string>	_http_methods;
	std::string				_redirection;
	std::string				_root;
	bool 					_autoindex;
	std::string				_upload_dir;
	std::string 			_cgi;

private:
	Route();

public:
	Route(std::string root, std::set<std::string> default_pages);
	~Route();
	void	parseRoute(std::ifstream& file, std::vector<std::string>& command);
	void	showInfo() const;
	const std::string& getRoute() const;
	const std::set<std::string>& getDefaultPages() const;
	const std::set<std::string>& getHTTPmethods() const;
	const std::string& getRedirection() const;
	bool getAutoindex() const;
	const std::string& getRoot() const;
	const std::string& getUploadDirectory() const;
	const std::string& getCGI() const;


private:
	void parseFirstStr(std::ifstream& file,
						 std::vector<std::string>& command);
	void parseHTTPmethods(std::vector<std::string>& command);
	void parseRedirection(std::vector<std::string>& command);
	void parseRoot(std::vector<std::string>& command);
	void parseIndex(std::vector<std::string>& command);
	void parseAutoindex(std::vector<std::string>& command);
	void parseUploadDir(std::vector<std::string>& command);
	void parseCGI(std::vector<std::string>& command);
};




#endif
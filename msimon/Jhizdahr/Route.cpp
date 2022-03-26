#include "Route.hpp"

Route:: Route(std::string root, std::set<std::string> default_pages) :
			_route(),
			_default_pages(default_pages),
			_http_methods(),
			_redirection(),
			_root(root),
			_autoindex(false),
			_upload_dir("/downloads"),
			_cgi() {

		_http_methods.insert("GET");
		_http_methods.insert("POST");
		_http_methods.insert("DELETE");
		_default_pages.insert("index.html");
}

Route:: ~Route() {}

void Route::parseFirstStr(std::ifstream& file,
						  std::vector<std::string>& command) {

	if (command.size() < 2)
		throw std::logic_error("Syntax error in location block");
	if (command[1][0] != '/')
		throw std::logic_error("Syntax error in location route");
	_route = command[1];
	_root += _route;
	if (command[2] == "{")
		return ;
	command.clear();
	std::string str;
	while (std::getline(file, str)) {
		if (str.empty())
			continue ;
		if (str == "{")
			return ;
		else
			throw (std::logic_error("Commands outside brackets in location"));
	}
	throw (std::logic_error("No opening brackets in location"));
}

void Route::parseHTTPmethods(std::vector<std::string>& command) {

	if (command.size() < 2)
		throw (std::logic_error("Syntax error in HTTP_methods"));
	_http_methods.clear();
	for (size_t i = 1; i < command.size(); ++i) {
		if (command[i] != "GET" && command[i] != "POST" &&
			command[i] != "DELETE")
			throw std::logic_error("Invalid http method in config");
		_http_methods.insert(command[i]);
	}
}
void Route::parseRedirection(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in route redirection"));
	_redirection = command[1];
}

void Route::parseRoot(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in route root config"));
	if (command[1][0] != '/')
		throw (std::logic_error("Syntax error in route root config"));
	_root = command[1];
}

void Route::parseIndex(std::vector<std::string>& command) {

	if (command.size() < 2)
		throw (std::logic_error("Syntax error in route index config"));
	_default_pages.clear();
	for (size_t i = 1; i < command.size(); ++i)
		_default_pages.insert(command[i]);
}

void Route::parseAutoindex(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in autoindex config"));
	if (command[1] == "on")
		_autoindex = true;
	else if (command[1] != "off")
		throw (std::logic_error("Syntax error in autoindex config"));
}

void Route::parseUploadDir(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in upload directory config"));
	if (command[1][0] != '/')
		throw (std::logic_error("Syntax error in upload directory config"));
	_upload_dir = command[1];
}

void Route::parseCGI(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in cgi config"));
	_cgi = command[1];
}

void Route::parseRoute(std::ifstream& file, std::vector<std::string>& command) {

	try {
		parseFirstStr(file, command);
	}
	catch (std::logic_error& e) {
		throw;
	}
	std::string str;
	bool in_brackets = true;
	while (getline(file, str)) {
		if (str.empty())
			continue;
		if (str == "}") {
			in_brackets = false;
			break;
		}
		command = str_split(str);
		if (command[0] == "http_methods") {
			try {
				parseHTTPmethods(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "redirection") {
			try {
				parseRedirection(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "root") {
			try {
				parseRoot(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "index") {
			try {
				parseIndex(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "autoindex") {
			try {
				parseAutoindex(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "upload_directory") {
			try {
				parseUploadDir(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "cgi") {
			try {
				parseCGI(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else
			throw std::logic_error("No such option in location config");
		command.clear();
	}
	if (in_brackets)
		throw (std::logic_error("Brackets unclosed in loctaion config"));
}

const std::string& Route::getRoute() const {
	return _route;
}

const std::set<std::string>& Route::getDefaultPages() const {
	return _default_pages;
}

const std::set<std::string>& Route::getHTTPmethods() const {
	return _http_methods;
}

const std::string& Route::getRedirection() const {
	return _redirection;
}

bool Route::getAutoindex() const {
	return _autoindex;
}

const std::string& Route::getRoot() const {
	return _root;
}

const std::string& Route::getUploadDirectory() const {
	return _upload_dir;
}

const std::string& Route::getCGI() const {
	return _cgi;
}

void Route::showInfo() const {

	std::cout << "LOCATION " << std::endl;
	std::cout << "route " << _route << std::endl;
	std::cout << "default pages ";
	for (std::set<std::string>::iterator
				 it = _default_pages.begin(); it != _default_pages.end(); ++it) {
		std::cout <<  *it << " ";
	}
	std::cout << std::endl;
	std::cout << "http methods ";
	for (std::set<std::string>::iterator
				 it = _http_methods.begin(); it != _http_methods.end(); ++it) {
		std::cout <<  *it << " ";
	}
	std::cout << std::endl;
	std::cout << "redirection " << _redirection << std::endl;
	std::cout << "root " << _root << std::endl;
	std::cout << "autoindex " << _autoindex << std::endl;
	std::cout << "upload dir " << _upload_dir << std::endl;
}
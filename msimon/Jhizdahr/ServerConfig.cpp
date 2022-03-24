#include "ServerConfig.hpp"

ServerConfig::ServerConfig() :
	_request_address(),
	_server_names(),
	_error_pages(),
	_default_pages(),
	_root("/www"),
	_limit_body_size(1000000),
	_routes() {

	_request_address.push_back(std::pair<in_addr_t, int>
	        (inet_addr("0.0.0.0"),80));
	_default_pages.insert("index.html");
	_server_names.insert(std::string());
	fill_errors();
}

ServerConfig::~ServerConfig() {}

void ServerConfig::fill_errors() {

	std::ifstream file("errors.txt");
	std::string str;
	std::string str1;
	while (std::getline(file, str)) {
		str1 = str.substr(0, str.find(" "));
		str.erase(0, str.find(" ") + 1);
		_error_pages.insert(std::pair<int, std::string>(str_to_int(str1),
														str));
	}
	file.close();
}

void ServerConfig::parseRequestAddress(std::vector<std::string>& command) {

	if (command.size() == 1)
		throw std::logic_error("Config syntax error in listen");
	for (size_t i = 1; i < command.size(); ++i) {
		if (i > _request_address.size())
			_request_address.push_back(std::make_pair(inet_addr("0.0.0.0"),80));
		size_t colon_pos = command[i].find(":");
		if (colon_pos != std::string::npos) {
			std::string ip_addr = command[i].substr(0, colon_pos);
			if (!ifIPvalid(ip_addr))
				throw std::logic_error("Invalid IP address");
			_request_address.back().first = inet_addr(ip_addr.c_str());
			if (_request_address.back().first == INADDR_NONE)
				throw std::logic_error("Invalid IP address");
			_request_address.back().second = str_to_int(command[i].substr
					(colon_pos + 1, command[i].size() - colon_pos));
			if (_request_address.back().second > 65535 || _request_address
			.back().second < 0)
				throw std::logic_error("Invalid port");
		}
		else if (command[i].find(".") != std::string::npos) {
			if (!ifIPvalid(command[i]))
				throw std::logic_error("Invalid IP address");
			_request_address.back().first = inet_addr(command[i].c_str());
			if (_request_address.back().first == INADDR_NONE)
				throw (std::logic_error("Invalid IP address"));
		}
		else {
			_request_address.back().second = str_to_int(command[i].substr
					(0, command[i].size()));
			if (_request_address.back().second > 65535 ||
				_request_address.back().second < 0)
				throw std::logic_error("Invalid port");
		}
	}
}

void ServerConfig::parseServerNames(std::vector<std::string>& command) {

	if (command.size() == 1)
		throw std::logic_error("Config syntax error in server_name");
	_server_names.clear();
	for (size_t i = 1; i < command.size(); ++i) {
		_server_names.insert(command[i]);
	}
}

void ServerConfig::parseErrorPages(std::vector<std::string>& command) {

	if (command.size() < 3)
		throw std::logic_error("Config syntax error in server_name");
	for (size_t i = 1; i < command.size() - 1; ++i) {
		int num = str_to_int(command[i]);
		if (num < 0)
			throw std::logic_error("Config syntax error in error_pages");
		if (_error_pages.count(num))
			_error_pages[num] = command[command.size() - 1];
		else
			throw std::logic_error("No such error number in error_pages");
	}
}

void ServerConfig::parseRoot(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw std::logic_error("Config syntax error in root");
	if (command[1][0] != '/')
		throw std::logic_error("Config syntax error in root: root should "
							   "begin with /");
	_root = command[1];
}

void ServerConfig::parseIndex(std::vector<std::string>& command) {

	if (command.size() < 2)
		throw std::logic_error("Config syntax error in index");
	_default_pages.clear();
	for (size_t i = 1; i < command.size(); ++i)
		_default_pages.insert(command[i]);
}

void ServerConfig::parseClientMaxBodySize(
		std::vector<std::string>& command) {

	if (command.size() != 2)
		throw std::logic_error("Config syntax error in client_max_body_size");
	int num = str_to_int(command[1]);
	if (num < 0)
		throw std::logic_error("Config syntax error in client_max_body_size");
	_limit_body_size = num;
}

void ServerConfig::parseRoutePreporation(std::ifstream& file,
											std::vector<std::string>& command) {

	_routes.push_back(Route(_root, _default_pages));
	try {
		_routes.back().parseRoute(file, command);
	}
	catch (std::logic_error& e) {
		throw;
	}
}

void ServerConfig::parseServer(std::ifstream& file) {

	std::string str;
	bool in_brackets = true;
	while (std::getline(file, str)) {
		if (str.empty())
			continue;
		if (str == "}") {
			in_brackets = false;
			break;
		}
		std::vector<std::string> command = str_split(str);
		if (command[0] == "listen") {
			try {
				parseRequestAddress(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "server_name") {
			try {
				parseServerNames(command);
			}
			catch (std::logic_error& e) {
				throw ;
			}
		}
		else if (command[0] == "error_page") {
			try {
				parseErrorPages(command);
			}
			catch (std::logic_error& e) {
				throw ;
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
		else if (command[0] == "client_max_body_size") {
			try {
				parseClientMaxBodySize(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "location") {
			try {
				parseRoutePreporation(file, command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else
			throw std::logic_error("Invalid option in config found");
		command.clear();
	}
	if (in_brackets)
		throw std::logic_error("Config error: brackets unclosed");
}

bool ServerConfig::ifIPvalid(std::string& ip_address) {

	int points = 0;
	for (size_t i = 0; i < ip_address.size(); ++i) {
		if (ip_address[i] == '.')
			++points;
	}
	if (points == 3)
		return true;
	return false;
}

const std::vector<std::pair<in_addr_t, int> >&
        ServerConfig::getVectorOfAddresses() const {
	return _request_address;
}

const std::set<std::string>& ServerConfig::getServerNames() const {
	return _server_names;
}

const std::map<int, std::string>& ServerConfig::getErrorPages() const {
	return _error_pages;
}

const std::set<std::string>& ServerConfig::getDefaultPages() const {
	return _default_pages;
}

int ServerConfig::getBodySizeLimit() const {
	return _limit_body_size;
}

const std::string& ServerConfig::getRootOfServer() const {
	return _root;
}

const std::vector<Route>& ServerConfig::getServerRoutes() const {
	return _routes;
}

void ServerConfig::showInfo() const {

	for (std::vector<std::pair<in_addr_t, int> >::const_iterator
	it = _request_address.begin(); it != _request_address.end();
		 ++it) {
		std::cout << "ip " << it->first << std::endl;;
		std::cout << "port " << it->second << std::endl;
	}
	std::cout << "server_name ";
	for (std::set<std::string>::const_iterator
				 it = _server_names.begin(); it != _server_names.end(); ++it) {
		std::cout <<  *it << " ";
	}
	std::cout << std::endl;
	for (std::map<int, std::string>::const_iterator it = _error_pages.begin()
			; it
	!= _error_pages.end(); ++it) {
		std::cout << it->first << " " << it->second << std::endl;
	}
	std::cout << "default pages ";
	for (std::set<std::string>::iterator
				 it = _default_pages.begin(); it != _default_pages.end(); ++it) {
		std::cout <<  *it << " ";
	}
	std::cout << std::endl;
	std::cout << "root " << _root << std::endl;
	std::cout << "limit body size " << _limit_body_size << std::endl;
	for (std::vector<Route>::const_iterator it = _routes.begin(); it != _routes
	.end(); ++it) {
		it->showInfo();
	}
}
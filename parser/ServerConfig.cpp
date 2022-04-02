#include "ServerConfig.hpp"

ServerConfig::ServerConfig() :
	_request_address(),
	_server_names(),
	_error_pages(),
	_default_pages(),
	_root("/www"),
	_limit_body_size(1000000),
	_tmp_files("/tmp"),
	_routes() {

	_request_address.push_back(std::pair<in_addr_t, int>
	        (inet_addr("0.0.0.0"), 80));
	_default_pages.insert("index.html");
	_server_names.insert(std::string());
	_routes.push_back(Route("/", _root, _default_pages, _tmp_files,
							_error_pages));
}

ServerConfig::~ServerConfig() {}

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
		if (num < 100 || num > 505)
			throw std::logic_error("Config syntax error in error_pages: no "
								   "such code of error");
		_error_pages[num] = command[command.size() - 1];
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

void ServerConfig::parseTmpDir(std::vector <std::string>& command) {

	if (command.size() != 2)
		throw std::logic_error("Config syntax error in tmp_files");
	if (command[1][0] != '/')
		throw std::logic_error("Config syntax error in tmp_files: tmp_files "
							   "argument should begin with /");
	_tmp_files = command[1];
}

void ServerConfig::parseRoutePreporation(std::ifstream& file,
											std::vector<std::string>& command) {

	if (command.size() < 2)
		throw std::logic_error("Syntax error in location block");
	if (command[1][0] != '/')
		throw std::logic_error("Syntax error in location route");
	if (command[1] != "/")
		_routes.push_back(Route(command[1], _root, _default_pages,
								_tmp_files, _error_pages));
	try {
		if (command[1] == "/")
			_routes.front().parseRoute(file, command);
		else
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
		else if (command[0] == "tmp_files") {
			try {
				parseTmpDir(command);
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

int ServerConfig::getBodySizeLimit() const {
	return _limit_body_size;
}

const std::vector<Route>& ServerConfig::getServerRoutes() const {
	return _routes;
}

const Route* ServerConfig::chooseRoute(const std::string& urlRoute) const {

	const std::vector<Route>& vecRoute = getServerRoutes();
	const Route* res = &(vecRoute.front());
	if (urlRoute.empty() || urlRoute == "/")
		return res;
	size_t maxDirs = 0;
	std::vector<std::string> urlParsed = strSplitBySlash(urlRoute);
	for (std::vector<Route>::const_iterator it = vecRoute.begin(); it !=
	vecRoute.end(); ++it) {
		std::vector<std::string> routeParsed = strSplitBySlash(it->getRoute());
		size_t i = 0;
		while (i < routeParsed.size() && i < urlParsed.size()) {
			if (routeParsed[i] == urlParsed[i])
				++i;
			else
				break;
		}
		if (i > maxDirs && i == routeParsed.size()) {
			maxDirs = i;
			res = &(*it);
		}
		routeParsed.clear();
	}
	return res;
}
const std::map<int, std::string>& ServerConfig::getErrorPages() const {
	return _error_pages;
}
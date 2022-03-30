#include "GetServer.hpp"

std::string GetServer::parseServerName(const std::string& host) {

	std::string res;
	size_t pos = host.find(':');
	if (pos == std::string::npos)
		return host;
	res = host.substr(0, host.length() - pos);
	return res;
}

const ServerConfig* GetServer::chooseServer(connect_t* conn,
											const std::vector <ServerConfig>& config) {

	std::string reqServerName = parseServerName(conn->head.get("host"));
	for (std::vector<ServerConfig>::const_iterator it = config.begin();
		 it != config.end(); ++it) {
		std::set<std::string> serverNames = it->getServerNames();
		for (std::set<std::string>::iterator iter = serverNames.begin(); iter
		!= serverNames.end(); ++iter) {
			if (*iter == reqServerName)
				return &(*it);
		}
	}
	return &(config[0]);
}

bool GetServer::checkHTTPMethodAllowed(const std::string& method,
									   const Route* route) {
	std::set<std::string> HTTPmethods = route->getHTTPmethods();
	for (std::set<std::string>::iterator
				 it = HTTPmethods.begin(); it != HTTPmethods.end(); ++it) {
		if (*it == method)
			return true;
	}
	return false;
}

void GetServer::getConfigInformation(connect_t* conn,
									 const std::vector <ServerConfig>& config) {

	if (conn->head.get("http") != "HTTP/1.1")
		throw std::runtime_error("505");
	std::string method = conn->head.get("method");
	ServerConfig* server = chooseServer(conn, config);
	if (str_to_int(conn->head.get("content-length")) >
	server->getBodySizeLimit())
		throw std::runtime_error("413");
	std::string HTTPmethod = conn->head.get("method");
	if (HTTPmethod != "GET" && HTTPmethod != "HEAD" && HTTPmethod != "PUT" &&
	HTTPmethod != "POST" && HTTPmethod != "DELETE")
		throw std::runtime_error("501");
	const std::vector<Route>& vecRoute = server->getServerRoutes();
	const Route* res = &(vecRoute.front());
	std::string uri = conn->head.get("uri");
	if (uri.length() > 8192)
		throw std::runtime_error("414");
	if (uri.empty() || uri == "/") {
		if (!checkHTTPMethodAllowed(method, res))
			throw std::runtime_error("405");
		conn->config = res;
		return;
	}
	size_t maxDirs = 0;
	std::vector<std::string> urlParsed = strSplitBySlash(uri);
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
	if (!checkHTTPMethodAllowed(method, res))
		throw std::runtime_error("405");
	conn->config = res;
}

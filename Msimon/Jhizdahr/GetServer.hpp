#ifndef WEBSERV_GETSERVER_HPP
#define WEBSERV_GETSERVER_HPP

#include "ServerConfig.hpp"
#include "Route.hpp"
#include "Connect.hpp"
#include "utils.hpp"

class GetServer {

public:
	void getConfigInformation(connect_t* conn, const std::vector<ServerConfig>&
		config);
	const ServerConfig* chooseServer(connect_t* conn,
												const std::vector
												        <ServerConfig>& config);

private:
	int checkServerIPs(in_addr_t reqIP, int reqPort,
					   std::vector<std::pair<in_addr_t, int> >& confReqAddr);
	bool checkHTTPMethodAllowed(const std::string& method, const Route* route);
	std::string parseServerName(const std::string& host);
};


#endif

#include <iostream>
#include "ServerConfig.hpp"
#include "ConfigParser.hpp"
#include "utils.hpp"
#include "GetServer.hpp"

void showInfo(ConfigParser& config) {

	std::vector<ServerConfig> arrServer = config.getVectorOfServers();
	for (std::vector<ServerConfig>::iterator it = arrServer.begin();
		 it != arrServer.end(); ++it) {

		//IP and ports
		std::vector<std::pair<in_addr_t, int> >
		        IPandPorts = it->getVectorOfAddresses();
		for (std::vector<std::pair<in_addr_t, int> >::iterator
		it = IPandPorts.begin(); it != IPandPorts.end(); ++it) {
			std::cout << "IP " << it->first << " ";
			std::cout << "port " << it->second << std::endl;
		}

		//Server names
		std::set<std::string> serverNames = it->getServerNames();
		std::cout << "server_name ";
		for (std::set<std::string>::iterator
		it = serverNames.begin(); it != serverNames.end(); ++it) {
			std::cout <<  *it << " ";
		}
		std::cout << std::endl;

		//Error pages
		std::cout << "error pages: " << std::endl;
		std::map<int, std::string> errorPages = it->getErrorPages();
		for (std::map<int, std::string>::const_iterator it2 = errorPages.begin();
			 it2 != errorPages.end(); ++it2) {
			std::cout << it2->first << " " << it2->second << std::endl;
		}

		//Server root
		std::string root = it->getRootOfServer();
		std::cout << "root " << root << std::endl;

		//Body size limit
		int limitBodySize = it->getBodySizeLimit();
		std::cout << "limit body size " << limitBodySize << std::endl;

		//Routes (директива location)
		std::cout << "Routes: " << std::endl;
		std::vector<Route> arrRoute = it->getServerRoutes();
		for (std::vector<Route>::iterator iter = arrRoute.begin(); iter !=
		arrRoute.end(); ++iter) {

			//Route name
			std::string routeName  = iter->getRoute();
			std::cout << "Route name " << routeName << std::endl;

			//Default pages (index)
			std::set<std::string> defaultPages = iter->getDefaultPages();
			std::cout << "default pages ";
			for (std::set<std::string>::iterator
						 it = defaultPages.begin(); it != defaultPages.end(); ++it) {
				std::cout <<  *it << " ";
			}
			std::cout << std::endl;

			//HTTP methods
			std::set<std::string> HTTPmethods = iter->getHTTPmethods();
			std::cout << "http methods ";
			for (std::set<std::string>::iterator
			it = HTTPmethods.begin(); it != HTTPmethods.end(); ++it) {
				std::cout <<  *it << " ";
			}
			std::cout << std::endl;

			//Redirection (string)
			std::cout << "redirection " << iter->getRedirection() << std::endl;

			//Root (string)
			std::cout << "root " << iter->getRoot() << std::endl;

			//Autoindex (bool) - показывать ли внутренности директории, если
			// основной файл не найден
			std::cout << "autoindex " << iter->getAutoindex() << std::endl;

			//Upload directory (string)
			std::cout << "upload directory " << iter->getUploadDirectory() <<
			std::endl;

			//Tmp directory (string)
			std::cout << "tmp files " << iter->getTmpFilesDir() <<
					  std::endl;

			//Error pages
			std::cout << "error pages: " << std::endl;
			std::map<int, std::string> errorPages = iter->getErrorPages();
			for (std::map<int, std::string>::const_iterator it2 =
					errorPages.begin(); it2 != errorPages.end(); ++it2) {
				std::cout << it2->first << " " << it2->second << std::endl;
			}

			//CGI (string)
			std::cout << "CGI " << iter->getCGI() << std::endl;

			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}


int main(int argc, char **argv) {

	if (argc == 1) {
		std::cerr << "There is no config file" << std::endl;
		return 1;
	}
	if (argc > 2) {
		std::cerr << "Only one config file needed" << std::endl;
		return 1;
	}
	ConfigParser config = ConfigParser(argv[1]);
	try {
		config.ParsingProcess();
	}
	catch (std::logic_error& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	//showInfo(config);
	std::string servName = std::string();
	const ServerConfig* server = chooseServer(inet_addr("0.0.0.0"), 80,
											  servName, config.getVectorOfServers());
	//IP, порт и server_name приходят с request, нужно интегрировать
	// chooseServer с каким-то из классов, пока не знаю с каким
	if (server == NULL) {
		std::cerr << "Server not found" << std::endl;
		return 1;
	}
	std::cout << "root of server: " << server->getRootOfServer() << std::endl;
	//чтобы проверить правильный выбор сервера
	std::string partURI = "another/dir";
	const Route* serverRoute = server->chooseRoute(partURI);
	std::cout << "chosen route: " << serverRoute->getRoute() << std::endl;
	//чтобы
	// проверить правильный выбор маршрута*/
}
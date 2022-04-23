#include "ServerManager.hpp"
#include "ServerConfig.hpp"
#include "ConfigParser.hpp"
#include "utils.hpp"

int main(int argc, char **argv) {

	ServerManager sm;
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

	for (std::vector<ServerConfig>::const_iterator
	it = config.getVectorOfServers().begin();
	it != config.getVectorOfServers().end();
	++it)
	{
		sm.servers.push_back(*it);
	}
	sm.Launch();
}

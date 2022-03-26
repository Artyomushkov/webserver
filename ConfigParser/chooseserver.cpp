#include "ServerConfig.hpp"

int checkServerIPs(in_addr_t reqIP, int reqPort,
				   std::vector<std::pair<in_addr_t, int> >& confReqAddr) {

	if (reqIP == 0)
		return 2;
	int IPcompliance = 0;
	for (std::vector<std::pair<in_addr_t, int> >::iterator it2 =
			confReqAddr.begin(); it2 != confReqAddr.end(); ++it2) {
		if (reqIP == it2->first && reqPort == it2->second) {
			return 2;
		}
		else if (it2->first == 0 && reqPort == it2->second &&
				 IPcompliance == 0) {
			IPcompliance = 1;
		}
	}
	return IPcompliance;
}

const ServerConfig* chooseServer(in_addr_t reqIP, int reqPort, const
std::string& reqServerName, const std::vector<ServerConfig>& config) {

	const ServerConfig* res = NULL;
	for (std::vector<ServerConfig>::const_iterator it = config.begin();
			it != config.end(); ++it) {
		std::vector<std::pair<in_addr_t, int> > confReqAddr =
				it->getVectorOfAddresses();
		int maxIPcompliance = 0;
		bool resServNameCompliance = false;
		int servIPcompliance = checkServerIPs(reqIP, reqPort, confReqAddr);
		bool servNameCompliance = false;
		if (maxIPcompliance <= servIPcompliance && servIPcompliance != 0) {
			std::set<std::string> confServerNames = it->getServerNames();
			for (std::set<std::string>::iterator it3 = confServerNames.begin();
					it3 != confServerNames.end(); ++it3) {
				if (reqServerName == *it3) {
					if (servIPcompliance == 2)
						return &(*it);
					servNameCompliance = true;
				}
			}
		}
		if (servIPcompliance != 0) {
			if (servIPcompliance > maxIPcompliance) {
				res = &(*it);
				maxIPcompliance = servIPcompliance;
				resServNameCompliance = servNameCompliance;
			} else if (servIPcompliance == maxIPcompliance) {
				if (resServNameCompliance == false &&
					servNameCompliance == true) {
					res = &(*it);
					resServNameCompliance = servNameCompliance;
				}
			}
		}
	}
	return res;
}


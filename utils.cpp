#include "utils.hpp"

std::vector<std::string> str_split(const std::string& str) {

	std::vector<std::string> res;
	int pos;
	int len;
	for (size_t i = 0; i < str.size(); ++i) {
		while (std::isspace(str[i]))
			++i;
		if (i == str.size())
			return res;
		pos = i;
		len = 0;
		while (!(std::isspace(str[i]))) {
			++i;
			++len;
			if (i == str.size())
				break;
		}
		res.push_back(str.substr(pos, len));
	}
	return res;
}

int str_to_int(const std::string& str) {

	for (size_t i = 0; i < str.size(); ++i) {
		if (!isdigit(str[i]))
			return (-1);
	}
	const char* cstr = str.c_str();
	char*	p_end;
	return strtol(cstr, &p_end, 10);
}


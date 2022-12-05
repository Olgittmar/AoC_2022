#include "GetUserName.hpp"

#include <iostream>
#include <string>

namespace utils {

auto GetUserName(std::ostream& out, std::istream& input) -> std::string
{
	std::string username;
	out << "Please enter your name: ";
	std::getline(input, username);
	return username;
}

} // namespace utils

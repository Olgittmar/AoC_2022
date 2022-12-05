#include "Hello.hpp"

#include <Utils.hpp>
#include <vector>

namespace Hello {

void
PrintHelloWorld(std::ostream& out)
{
    out << "Hello world!\n";
}

void
PrintHelloUser(std::ostream& out, std::istream& input)
{
    std::string username = utils::GetUserName(out, input);

    if (username.empty()) {
	out << "Hello world!\n";
	return;
    }

    out << "Hello " << username << "!\n";
}

} // namespace Hello

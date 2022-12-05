#ifndef HELLO_HELLO_HPP
#define HELLO_HELLO_HPP

#include <iostream>
#include <istream>

namespace Hello {

void PrintHelloWorld(std::ostream& out);
void PrintHelloUser(std::ostream& out, std::istream& input);

} // namespace Hello
#endif
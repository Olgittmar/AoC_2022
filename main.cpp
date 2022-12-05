#include <Hello.hpp>
#include <iostream>

auto
main() -> int
{
    Hello::PrintHelloUser(std::cout, std::cin);
}
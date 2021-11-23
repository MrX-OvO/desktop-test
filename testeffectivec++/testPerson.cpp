#include <iostream>
#include <string>
#include "Person.h"

int main(int argc, char const *argv[])
{
    std::string name = "MrX";
    Date date(23, 5, 2000);
    std::string addr = "China Shanghai";
    Person p(name, date, addr);
    std::cout << "Person p\n"
              << p;

    return 0;
}

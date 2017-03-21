#include "BigGuys.h"

#ifndef some_useful_libs
    #include <iostream>
#endif

int main()
{
	std::string zxc;
	std::getline(std::cin, zxc);
    BigGuys foo(zxc.c_str()), bar;
    bar = foo;
    BigGuys kekker(bar);

    std::getline(std::cin, zxc);
    BigGuys temp(zxc.c_str());
//    std::cout << temp << temp.get_len() << std::endl;
    std::cout << temp + kekker;

    return 0;
}

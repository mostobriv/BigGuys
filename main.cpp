#include "BigGuys.h"

#ifndef some_useful_libs
    #include <iostream>
#endif

int main()
{
  /*
	std::string zxc;
	std::getline(std::cin, zxc);
    BigGuys foo(zxc.c_str()), bar;
    bar = foo;
    BigGuys kekker(bar);

    std::getline(std::cin, zxc);
    BigGuys temp(zxc.c_str());
//    std::cout << temp << temp.get_len() << std::endl;
    //std::cout << temp + kekker;
    std::cout << temp << temp.get_len() << temp.get_cap() << std::endl;
*/
  std::string qw;
  std::getline(std::cin, qw);
  BigGuys foo(qw.c_str());
  std::cout << foo;
    return 0;
}

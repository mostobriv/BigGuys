#include "BigGuys.rel.h"

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

  std::string foo, bar;
  std::getline(std::cin, foo);
  std::getline(std::cin, bar);
  BigGuys<short unsigned int> lol(foo.c_str()), kek(bar.c_str());
  //std::cout << "LOL - " << lol << "KEK - " << kek;
  std::cout << lol * kek;
  return 0;
}

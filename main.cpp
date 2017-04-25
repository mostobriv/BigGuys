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
/*
  std::string foo, bar;
  std::getline(std::cin, foo);
  std::getline(std::cin, bar);
  BigGuys<unsigned short int> lol(foo.c_str());
  unsigned short int kek = std::stoul(bar, nullptr, 16);
*/
  /*
  BigGuys<unsigned short int> lol(foo.c_str()), kek(bar.c_str());
  //std::cout << "LOL - " << lol << "KEK - " << kek;
  */

/*
  std::string foo, bar;
  std::getline(std::cin, foo);
  std::getline(std::cin, bar);
  unsigned short int kek = std::stoul(bar, nullptr, 16);
  BigGuys<unsigned short int> lol(foo.c_str());

  auto tmp = lol.div_base(kek);

  std::cout << std::get<0>(tmp);

  std::cout.unsetf(std::ios::dec);
  std::cout.setf(std::ios::hex | std::ios::uppercase);


  std::cout << std::get<1>(tmp) << std::endl;


  std::cout.unsetf(std::ios::hex | std::ios::uppercase);
  std::cout.setf(std::ios::dec);
*/
    std::string foo;
    std::getline(std::cin, foo);

    BigGuys<unsigned short int> kek(foo.c_str());

    std::cout << kek.power(0);
    std::cout << kek.power(1);
    std::cout << kek.power(4);

    return 0;
}

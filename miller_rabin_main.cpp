#include "BigGuys.rel.h"
#include <ctime>

int main() {

    BigGuys<unsigned short int> a("995A01");


    // std::cout << a;
    // std::cout << a.miller_rabin_is_prime(10) << std::endl;
    // BigGuys<unsigned short int> foo("1B02761F9C6B100F64E1B27A78330195DA1F6902CDEAF4C71C71C7");
    BigGuys<unsigned short int> foo;
    // std::cout << foo.prime_generator(10);
    // for(int i = 3; i < 40; i++) {
    std::cout << foo.prime_generator(100);
    // }

    // std::cout << foo.miller_rabin_is_prime(10) << std::endl;

    // while ( a.miller_rabin_is_prime(10) ) {
    //     a.gen_rand_vec(1000);
    // }

    // std::cout << "Here is your prime: " << a;

    return 0;
}
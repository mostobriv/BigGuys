#include "BigGuys.rel.h"
#include <ctime>

#define LOOPS           100
#define MAX_BIT_RANGE   100

int main() {

    // BigGuys<unsigned short int> a("6258A"), pw("1E89"), mod("F4481");
    // BigGuys<unsigned short int> a("6258A"), pw("10001"), mod("F4481");
    srand(time(NULL));
    // std::cout << a;
    // std::cout << "a.len = " << a.get_len() << std::endl;
    for (int i = 0; i < LOOPS; i++) {
        int a = (rand() & (MAX_BIT_RANGE - 1));
        int b = (rand() & (MAX_BIT_RANGE - 1));
        int c = (rand() & (MAX_BIT_RANGE - 1));
        BigGuys<unsigned short int> x("123"), pw("1B02761F9C6B100F64E1B27A78330195DA1F6902CDEAF4C71C71C7"), mod("1B02761F9C6B100F64E1B27A78330195DA1F6902CDEAF4C71C71C7");
        // x.gen_rand_vec(a);
        // pw.gen_rand_vec(b);
        // mod.gen_rand_vec(c);
        // BigGuys<unsigned short int> tmp("1"), ctr("0"), step("1");
        // while ( !(ctr == pw) ) {
        //     ctr = ctr + step;
        //     tmp = std::get<1>(tmp *  x / mod);
        // }
        // std::cout << (x.power(pw, mod) == tmp) << std::endl;
        std::cout << x.power(pw, mod);
        return 0;
    }

    // while ( a.miller_rabin_is_prime(10) ) {
    //     a.gen_rand_vec(1000);
    // }

    // std::cout << "Here is your prime: " << a;

    return 0;
}
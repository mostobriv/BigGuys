#include "BigGuys.rel.h"
#include <ctime>

#define LOOPS           100
#define MAX_BIT_RANGE   10000

int main() {

    clock_t MR_timestamp, VANILLA_timestamp;

    srand(time(NULL));

    BigGuys<unsigned short int> x("11F3055EE6CB59767E88EF81AE87541080C6A4975D6E17BB40D8BDAE439044BBC4BD4B58CA1E05FB8AEA9D0B31E47BC191B9551A182AF8AC478A53A9CD298B54BF8C34A75823593A3BECA32A56585D239CCE97DF95FEA37764DDB15E3B6B0B79708D6695CAA263869B271A63E9B077B02BDF78B68A4191795034C1F38490E5A5FF219EE7FE774D1DA81405278CEBC5CF92FA3AE88518B55DDB4BACC15B7A5D4AD706C47B65C5F29D7CBD9AC89FFDE64C1A719F33EF4B87987350736E92BDBDE60E7"), m("7A757E954736306771FAEBA2953760A456493E8FB36F6549CDE3DB3996D340B71105013AAC1E8E7C1C3062F89DCE25544A5662BBFAF8900114294BD0E0C1C2C5916FFAFDEF37D624167914965C4840246D");

    for(int i = 0; i < LOOPS; i++) {

        int a = (rand() & (MAX_BIT_RANGE - 1));
        int b = (((rand() & (MAX_BIT_RANGE - 1)) >> 1) + 1);
        // std::cout << "x.bit_len = " << a << std::endl;
        // std::cout << "m.bit_len = " << b << std::endl;
        
        // x.gen_rand_vec(a);
        // m.gen_rand_vec(b);
        if (x.get_len() < m.get_len()) continue;
        // std::cout << x.get_len() << std::endl << x.get_cap() << std::endl << m;
        // std::cout << m.get_len() << std::endl << m.get_cap() << std::endl << m;
        // std::cout << "oops\n";
        BigGuys<unsigned short int> foo, bar, mabase("10000"), tmp, ppp(100), ololo;
        // std::cout << "x = " << x;
        // std::cout << "m = " << m;
        try{
            ppp.kek();
            ppp[0] = m.get_len();
            // std::cout << "mabase.power(ppp, m) = " << mabase.power(ppp, m);
            tmp = mabase.power(ppp, m);
            // std::cout << "tmp = " << tmp;
            // std::cout << "x.MR(m) = " << x.MR(m);
            std::cout << x.MR(m);
            // x / m;
            // // if (x >= (tmp * m)) continue;
            // std::cout << "x < (tmp * m) = " << (!(x >= (tmp * m))) << std::endl;
            // ololo = tmp * m;
            foo = std::get<1>(x.MR(m) * tmp / m);
            // std::cout << "foo = " << foo;
            bar = std::get<1>(x / m);
            // std::cout << a << " - " << b << std::endl;
            // std::cout << (foo == bar) << std::flush;
            if (!(foo == bar)) {
                std::cout << "x = " << x;
                std::cout << "m = " << m;
                std::cout << "foo = " << foo;
                std::cout << "bar = " << bar;
                return -1;
            }
            // std::cout << "bar = " << bar;
            return 0;
            
        } catch(const std::runtime_error(& error)) {
            std::cout << error.what() << std::endl;
            return -1;
        }
    }

    return 0;
}
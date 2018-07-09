#include "BigGuys.rel.h"
#include <ctime>


int main(int argc, char** argv) {
    srand(time(NULL));
    BigGuys<unsigned short int> kek, lol;
    clock_t timestamp, karacuba_sum, vanilla_sum;
    BigGuys<unsigned short int> tmp1, tmp2;

    for (int i = 0; i < 1000; i++) {
        kek.gen_rand_vec(rand() % 10000 + 1);
        lol.gen_rand_vec(rand() % 10000 + 1);

        // timestamp = clock();

        if (!((kek * lol) == kek.karacuba_mul(lol))) {
            std::cout << kek << lol;
            return -1;
        }
        
        // timestamp = clock() - timestamp;

        // vanilla_sum+= timestamp;

        // timestamp = clock();

        // kek.karacuba_mul(lol);

        // kek * lol;

        // timestamp = clock() - timestamp;

        // karacuba_sum+= timestamp;

    }

    // std::cout << "karacuba_sum = " << karacuba_sum << std::endl;
    // std::cout << "vanilla_sum = " << vanilla_sum << std::endl;

    return 0;
}
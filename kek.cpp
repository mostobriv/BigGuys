#include <iostream>
#include <stdio.h>

int nod(int a, int b) {
    return b ? nod(b, a % b) : a;
}

int main() {
    std::cout << nod(3, 9);
    return 0;
}

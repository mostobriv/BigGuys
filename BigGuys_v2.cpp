#include "BigGuys_v2.h"

#define CHECK(some_str) { for(size_t i = 0; i < strlen(some_str); i++) {if (strchr("abcdefABCDEF1234567890", some_str[i]) == NULL) throw std::runtime_error("invalid character in string: non-hex value");}}
#define SYM_GROUP (sizeof(T)<<1)
#define MAX_VAL (1<<(sizeof(T)<<2) - 1)

BigGuys_v2::BigGuys(size_t cap) {
    len = 0;
    guy = new T[cap];
}

BigGuys_v2::BigGuys(string const) {

}


~BigGuys() {
    delete[] guy;
}

size_t BigGuys_v2::get_cap() const {
    return cap;
}

size_t BigGuys_v2::get_len() const {
    return len;
}

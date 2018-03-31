#include "BigGuys.h"
#include <stdio.h>

#define CHECK(some_str) { for(size_t i = 0; i < strlen(some_str); i++) {if (strchr("abcdefABCDEF1234567890", some_str[i]) == NULL) throw std::runtime_error("invalid character in string: non-hex value");}}
#define BASE_SIZE sizeof(T)
#define SYM_GROUP (BASE_SIZE<<1)
#define MAX_VAL ((1<<(sizeof(T)<<3)) - 1)
#define BITS_SIZE (BASE_SIZE<<3)
#define BASE (((size_t)MAX_VAL)+1)

template<typename T>
BigGuys<T>::BigGuys(size_t t) {
    len = 0;
    guy = new T[t];
    cap = t;
    memset(guy, 0, cap * BASE_SIZE);
}

template<typename T>
BigGuys<T>::BigGuys(BigGuys<T> const &src) {
    cap = src.cap;
    guy = new T[cap];
    memcpy(guy, src.guy, cap * BASE_SIZE);
    len = src.len;
}

template<typename T>
BigGuys<T>::BigGuys(string const src) {
    CHECK(src.c_str());

    if (src.length() == 0) {
        len = 0;
        cap = 0;
        guy = nullptr;
    } else {
        cap = src.length() / SYM_GROUP + 1;
        len = 0;
        guy = new T[cap];

        //string padding to full SYM_GROUP
        short int pad = src.length() % SYM_GROUP ? SYM_GROUP - src.length() % SYM_GROUP : 0;
        char* temp = new char[src.length() + pad + 1];
        memset(temp, '0', src.length() + pad);
        strcpy(temp+pad, src.c_str());

        for( long int i = strlen(temp)-SYM_GROUP; i >= 0; i-=SYM_GROUP) {
            T num = (T) strtoul(&temp[i], NULL, 16);
            guy[len++] = num;
            temp[i] = 0;
        }

        delete[] temp;
    }
    clear_insig();
}

template <typename T>
void BigGuys<T>::clear_insig() {
 //std::cout << "DEBUG START\n";
    if (len == 0)
        return;
    //printf("%p\n", guy);
    long int i;
    for(i = len - 1; i >= 0 && guy[i] == 0; i--);

    if (i == -1) {
        delete[] guy;
        guy = new T[1];
        guy[0] = 0;
        len = 1;
        cap = 1;
    } else {
        T* tmp = new T[i+1];
        for(long int j = 0; j <= i; j++)
            tmp[j] = guy[j];
        delete[] guy;
        guy = tmp;
        cap = i+1;
        len = i+1;
    }
    //std::cout << "DEBUG END\n";

}

template <typename T>
BigGuys<T>& BigGuys<T>::operator= (BigGuys<T> const& src) {
    delete[] guy;
    cap = src.cap;
    guy = new T[cap];
    memcpy(guy, src.guy, cap * BASE_SIZE);
    len = src.len;

    return *this;
}

template <typename T>
BigGuys<T> BigGuys<T>::operator+ (BigGuys<T> const & add) {
    size_t max_cap = cap > add.cap ? cap : add.cap;
    BigGuys<T> tmp(max_cap + 1);

    size_t OF = 0, i;
    for (i = 0; i < len && i < add.len; i++) {
        tmp.len++;
        tmp[i] = (guy[i] + add[i] + OF) & MAX_VAL;
        OF = (guy[i] + add[i] + OF) / (MAX_VAL + 1);
    }

    if (i == len && i < add.len) {
        for(; i < add.len; i++) {
            tmp.len++;
            tmp[i] = (add[i] + OF) & MAX_VAL;
            OF = (add[i] + OF) / (MAX_VAL + 1);
        }
    } else if (i == add.len && i < len) {
        for(; i < len; i++) {
            tmp.len++;
            tmp[i] = (guy[i] + OF) & MAX_VAL;
            OF = (guy[i] + OF) / (MAX_VAL + 1);
        }
    }
    tmp.len++;
    tmp[i] = OF;

    tmp.clear_insig();
    return tmp;
}

template <typename T>
BigGuys<T> BigGuys<T>::operator- (BigGuys<T> const & sub) {
    size_t max_cap = cap > sub.cap ? cap : sub.cap;
    BigGuys<T> tmp(max_cap);

    size_t OF = 0, i;
    for(i = 0; i < sub.len; i++) {
        tmp.len++;
        tmp[i] = (guy[i] - sub[i] - OF) & MAX_VAL;
        OF = (MAX_VAL - (guy[i] - sub[i] - OF)) / (MAX_VAL + 1);
    }

    if (i < len) {
        for(; i < len; i++) {
            tmp.len++;
            tmp[i] = (guy[i] - OF) & MAX_VAL;
            OF = (MAX_VAL - (guy[i] - OF)) / (MAX_VAL + 1);
        }
    }

    tmp.clear_insig();
    return tmp;
}

template <typename T>
BigGuys<T> BigGuys<T>::operator* (BigGuys<T> const & mul) {
    BigGuys<T> tmp(cap + mul.cap);
    tmp.len = len + mul.len;

    size_t OF, i, j;
    for(i = 0; i < len; i++) {
        if (guy[i] == 0)
            continue;

        for(j = 0, OF = 0; j < mul.len; j++) {
            size_t t = (size_t)guy[i] * (size_t)mul[j] + (size_t)tmp[i+j] + OF;
            tmp[i+j] = t & MAX_VAL;
            OF = t / (MAX_VAL + 1);
        }
        tmp[tmp.len - len + i] = OF;
    }

    tmp.clear_insig();
    return tmp;
}

template <typename T>
BigGuys<T> BigGuys<T>::mul_base(T mul) {
    BigGuys<T> tmp(cap + 1);
    tmp.len = len + 1;

    size_t OF, i;
    for(i = 0, OF = 0; i < len; i++) {
        size_t t = (size_t)guy[i] * mul + OF;
        tmp[i] = t & MAX_VAL;
        OF = t / (MAX_VAL + 1);
    }
    tmp[i] = OF;

    tmp.clear_insig();
    return tmp;
}

template <typename T>
std::tuple<BigGuys<T>, T> BigGuys<T>::div_base(T diver) {
    BigGuys<T> tmp(cap);
    tmp.len = len;

    long unsigned int r = 0, t = 0;
    for(int i = len-1; i >= 0; i--) {
        t = guy[i] + r * (MAX_VAL + 1);
        tmp[i] = t / diver;
        r = t % diver;
    }

    tmp.clear_insig();

    return std::make_tuple(tmp, (T)r);
}

template <typename T>
bool BigGuys<T>::operator >= (BigGuys<T> const &source) const {
    return !(source > (*this));
}


template <typename T>
std::tuple<BigGuys<T>, BigGuys<T>> BigGuys<T>::operator/ (BigGuys<T> & source) {
    BigGuys<T> this_copy, source_copy;
    this_copy = (*this);
    source_copy = source;

    int m = len - source.len;
    if( m<0 ){
        BigGuys<T> res("0");
        return std::make_tuple(res, this_copy);
    }

    if( source.len == 1 ){
        auto res = this->div_base(source.guy[0]);
        BigGuys<T> kek(1);
        kek.len = 1;
        kek.guy[0] = std::get<1>(res);

        return std::make_tuple(std::get<0>(res), kek);
    }

    unsigned int long temp = 0;
    //BASE long base = (BASE long)std::numeric_limits< BASE >::max()+1;
    BigGuys<T> r(m+1);
    r.len = m+1;
    size_t d = BASE / (source.guy[source.len-1]+1);
    *this = this->mul_base(d);
    source = source.mul_base(d);
    //std::cout << "-----------------\n" << (*this) << source << "-------------------\n";
    BigGuys<T> tmp(len+1);
    tmp.len = len+1;
    //std::cout << "some this.len " << len << std::endl;
    for(size_t i=0; i<len; ++i){
        tmp.guy[i] = guy[i];
    }
    //std::cout << tmp << "HUUUUUUUUUUUUUGE\n";
    tmp.guy[len] = 0;
    int n = source.len;
    for(int j=m; j>=0; --j){
        bool flag;
        BigGuys<T> tmp1(n+1);
        flag = false;
        temp = ((long unsigned int)(tmp.guy[j+n])*BASE + tmp.guy[j+n-1])/source.guy[n-1];
        unsigned int long tempr = ((long unsigned int)(tmp.guy[j+n])*BASE + tmp.guy[j+n-1])-temp*source.guy[n-1];
        while( (tempr < BASE) && ((temp*source.guy[n-2]) > (tempr*BASE + guy[j+n-2])) ){
            --temp;
            tempr += source.guy[n-1];
        }
        //std::cout << tmp << "some tmp\n";
        //std::cout << "temp after while-loop - " << temp << std::endl;
        //::cout << "Also n is - " << n << std::endl;
        for(int k=n; k>=0; --k){
            //std::cout << "IN FOR LOOP - " << tmp.guy[j+k] << std::endl;
            tmp1.guy[k] = tmp.guy[j+k];
        }
        tmp1.len = 4;
        //std::cout << "some tmp1 for WUT?\n" << tmp1;
        tmp1.len = tmp1.cap;
        //std::cout << tmp1.cap << "cap\n";
        for (long int t = tmp1.len - 1; t > 0; t--) {
            if (tmp1.guy[t] == 0)
                tmp1.len--;
            else
                break;
        }

        //std::cout << "some tmp1 for you " << tmp1;

        //std::cout << "LEFT SIDE\n" << tmp1 << "RIGHT SIDE\n"<< source.mul_base(temp);
        if( tmp1 >= source.mul_base(temp)){
            tmp1 = tmp1 - source.mul_base(temp);
        } else {
            //std::cout << "Not right branch\n";
            BigGuys<T> tmpBase(n+2);
            tmpBase.len = n+2;
            tmpBase.guy[n+1] = 1;
            tmp1 = (tmpBase - source.mul_base(temp)) + tmp1;
            flag = true;
        }
        //std::cout << "tmp1 on 4 step is " << tmp1 << "asdfastqwataw45t\n";
        r.guy[j] = temp;
        if( flag == true ){
            --r.guy[j];
            tmp1 = tmp1 + source;
        }
        for(int k=n; k>=0; --k){
            if( k < tmp1.len ){
                tmp.guy[j+k] = tmp1.guy[k];
            } else {
                tmp.guy[j+k] = 0;
            }
        }
        for (long int t = tmp.len - 1; t > 0; t--) {
            if (tmp.guy[t] == 0)
                tmp.len--;
            else
                break;
        }
        //std::cout << "KEK\n" << tmp << "KEK\n";
    }
    r.clear_insig();
    BigGuys<T> mod;
    mod = std::get<0>(tmp.div_base(d));

    source = source_copy;
    *this = this_copy;
    return std::make_tuple(r, mod);

}

template <typename T>
size_t BigGuys<T>::get_binary_len() const {
    /*
    Utility-Function to get amount of bits in BigGuy
    */
    auto len = get_len();
    auto last = this->guy[len-1];
    while (last != 0) {
        last>>= 1;
        len++;
    }

    return len;
}

template <typename T>
size_t BigGuys<T>::get_binary_index(size_t index) const {
    /*
    Utility-Function to get bit on index place in BigGuy vector
    */
    auto b = index / BITS_SIZE, i = index % BITS_SIZE;

    return (guy[b] & (1 << i)) == 0 ? 0 : 1;
}

template <typename T>
BigGuys<T> BigGuys<T>::power(const BigGuys<T>& pw, const BigGuys<T>& mod) const {
    BigGuys<T> q = (*this), z("1"), modb = mod;

    if (pw[0] == 1) {
        z = q;
    }


    for (size_t i = 1; i < pw.get_binary_len(); i++) {
        auto result = (q * q) / modb;
        q = std::get<1>(result);

        if (pw.get_binary_index(i) == 1) {
            auto result = (q * z) / modb;
            z = std::get<1>(result);
        }
    }


    return z;
}

template <typename T>
bool BigGuys<T>::operator> (BigGuys<T> const &cmp) const {
    if (len > cmp.len)
        return true;
    else if (len < cmp.len)
        return false;

    for (long int i = len-1; i >= 0; i--) {
        if (guy[i] > cmp[i])
            return true;
        else if (guy[i] < cmp[i])
            return false;
    }
}

template <typename T>
bool BigGuys<T>::operator==(BigGuys<T> const &source) {
    if (len != source.len) {
      return false;
    }

    for (long int i = 0; i < len; i++) {
      if (guy[i] != source[i]) {
        return false;
      }
    }

    return true;
}

template <typename T>
T& BigGuys<T>::operator[] (size_t i) const {
    if (i >= len) {
        std::cout << "Your index - " << i << std::endl;
        throw std::runtime_error("Invalid index(too big)");
    }

    return guy[i];
}

template<typename T>
std::istream& operator>> (std::istream& in, BigGuys<T>& foo) {
    string tmp;
    std::getline(std::cin, tmp);
    CHECK(tmp.c_str());
    BigGuys<T> temp(tmp);

    foo = temp;

    return in;
}

template<typename T>
std::ostream& operator<< (std::ostream& out, const BigGuys<T> &foo) {

    size_t i = foo.get_len() - 1;

    if (foo.get_len() == 0) {
        out << std::endl;
        return out;
    }

    out.unsetf(std::ios::dec);
    out.setf(std::ios::hex | std::ios::uppercase);


    std::cout << foo[i--];
    if (foo.get_len() != 1) {
        while(i > 0) {
            out << std::setfill('0') << std::setw(SYM_GROUP) << foo[i--];
        }
        out << std::setfill('0') << std::setw(SYM_GROUP) << foo[i];
    }
    out << std::endl;

    out.unsetf(std::ios::hex | std::ios::uppercase);
    out.setf(std::ios::dec);

    return out;
}

template<typename T>
BigGuys<T>::~BigGuys() {
    delete[] guy;
}

template<typename T>
size_t BigGuys<T>::get_cap() const {
    return cap;
}

template<typename T>
size_t BigGuys<T>::get_len() const {
    return len;
}

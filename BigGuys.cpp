#include "BigGuys.h"


#define check(some_str) { for(size_t i = 0; i < strlen(some_str); i++) {if (strchr("abcdefABCDEF1234567890", some_str[i]) == NULL) throw std::runtime_error("invalid character in string: non-hex value");}}

BigGuys::BigGuys(size_t cap)
{
    len = 0;
    guy = std::unique_ptr<BASE>(new BASE[cap]);
    memset(guy.get(), 0, sizeof(BASE)*cap);
}

BigGuys::BigGuys(BigGuys const & src)
{
    cap = src.cap;
    guy = std::unique_ptr<BASE>(new BASE[cap]);
    memset(guy.get(), 0, sizeof(BASE)*cap);
    for (len = 0; len < src.len; len++)
        guy.get()[len] = src[len];
}

BigGuys::BigGuys(char const * src)
{
    size_t src_len = strlen(src);

    check(src);

    
    if (src_len == 0) {

        len = 0;
        cap = 2;
        guy = std::unique_ptr<BASE>(new BASE[2]);   

    } else {
        

        cap = src_len / (sizeof(BASE)*2) + 1;
        len = 0;
        guy = std::unique_ptr<BASE>(new BASE[cap]);

        //std::cout << src_len << std::endl << src_len + ((sizeof(BASE)*2) - (src_len) % (sizeof(BASE)*2)) << std::endl;

        int pad = src_len % (sizeof(BASE)<<1) ? ((sizeof(BASE)<<1) - (src_len) % (sizeof(BASE)<<1)) : 0;
        char* temp = new char[src_len + pad + 1];  //padding to src_len countable string
        memset(temp, '0', src_len + pad);
        strcpy(temp+pad, src);

        //std::cout << temp << std::endl;

        for ( long int i = strlen(temp)-sizeof(BASE)*2; i >= 0; i-=sizeof(BASE)*2 ) {
            //std::cout << &temp[i] << std::endl;
            auto num = (BASE) strtoul(&temp[i], NULL, 16);
            guy.get()[len++] = num;
            /*
            if (len == cap) {
                auto kekker = guy.release();
                cap<<=1;
                guy = std::unique_ptr<BASE>(new BASE[cap]);
                memcpy(guy.get(), kekker, len*sizeof(BASE));
                delete[] kekker;
            }
            */

            temp[i] = 0;
        } 
        delete[] temp;
    }

    //std::cout << len << ' ' << cap << ' ' << guy.get()[0] << guy.get()[1] << guy.get()[2] << std::endl;

}

std::istream& operator >> (std::istream & in, BigGuys & foo)
{
    std::string tmp;
    std::getline(std::cin, tmp);
    check(tmp.c_str());
    BigGuys temp(tmp.c_str());

    //foo = temp;
    
    return in;
}


size_t BigGuys::get_len() const
{
    return len;
}

size_t BigGuys::get_cap() const 
{
    return cap;
}

BigGuys& BigGuys::operator= (BigGuys const& src)
{
    cap = src.cap;
    guy = std::unique_ptr<BASE>(new BASE[cap]);
    for(len = 0; len < src.len; len++)
        guy.get()[len] = src[len];

    return *this;
}

BigGuys BigGuys::operator+ (BigGuys const & src) const
{

    auto max = len > src.len ? len : src.len;
    auto min = len < src.len ? len : src.len;
    BigGuys res(max+1);
    res.len = max+1;
    size_t OF = 0, i;
    
    for(i = 0; i < min; i++) {
        res[i] = ((size_t)guy.get()[i] + (size_t)src[i] + OF) & 0xffff;         //BASE DEPEND
        OF = ((size_t)guy.get()[i] + (size_t)src[i]) >> 16;                     //BASE DEPEND
    }
    if (i < len) {

        for(; i < len; i++) {
            res[i] = ((size_t)guy.get()[i] + OF) & 0xffff;                      //BASE DEPEND
            OF = ((size_t)guy.get()[i] + OF) >> 16;                             //BASE DEPEND
        }  

    } else if(i < src.len) {

        for(; i < src.len; i++) {
            res[i] = ((size_t)src[i] + OF) & 0xffff;                            //BASE DEPEND
            OF = ((size_t)src[i] + OF) >> 16;                                   //BASE DEPEND
        }
    } else {
        res[i] = OF;
    }

    return res;

}



BASE& BigGuys::operator[] (size_t i) const
{
    //std::cout << i << ' ' << "THIS IS LENGTH " << len <<  ' ' << cap << std::endl;
    if (i >= len)
        throw std::runtime_error("invalid index in array (too big)");

    return guy.get()[i];
}

std::ostream& operator << (std::ostream & out, BigGuys const & foo)
{
    if (!foo.get_len()) {
        out << std::endl;
        return out;
    }

    out.unsetf(std::ios::dec);
    out.setf(std::ios::hex | std::ios::uppercase);
    
    bool NOT_NULL;
    long int i;
    for(i = foo.get_len()-1; i >= 0; i--) {
        if (foo[i] != 0) {
            NOT_NULL = true;
            break;
        }
    }

    if (i != -1) {
        out << foo[i--];
        for (; i >= 0; i--) {
            //std::cout << "KEK " << i << std::endl;
            out << std::setfill('0') << std::setw(sizeof(BASE)*2) << foo[i];
        }
        out << std::endl;
    } else {
        out << '0' << std::endl; 
    }

    out.unsetf(std::ios::hex | std::ios::uppercase);
    out.setf(std::ios::dec);
    return out;
}

//no need in destructor because of unique_prt CARL
BigGuys::~BigGuys() {}
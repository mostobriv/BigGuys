#include <iostream>
#include <memory>
#include <stdexcept>
#include <cstring>
#include <string>
#include <iomanip>

#define some_useful_libs 1
#define BASE  short unsigned int

class BigGuys {
    public:
        BigGuys(size_t cap=2);
        BigGuys(char const *);
        BigGuys(BigGuys const &);
        ~BigGuys();
        friend std::ostream& operator << (std::ostream &, BigGuys const &);
        friend std::istream& operator >> (std::istream &, BigGuys &);
        BASE& operator[] (size_t ) const;
        BigGuys operator+ (BigGuys const &) const;
        BigGuys operator- (BigGuys const &) const;
        BigGuys& operator= (BigGuys const&);
        size_t get_cap() const;
        size_t get_len() const;
     private:
        std::unique_ptr<BASE> guy;
        size_t len;
        size_t cap;
};
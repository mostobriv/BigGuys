#pragma once

#include <iostream>
#include <stdexcept>
#include <cstring>
#include <string>
#include <iomanip>

using std::string;

template <typename T>
class BigGuys {
    public:
      BigGuys(size_t cap=0);
      BigGuys(string const);
      BigGuys(BigGuys<T> const &);
      ~BigGuys();
      T& operator[] (size_t) const;
      BigGuys<T>& operator= (BigGuys<T> const &);
      template<class U> friend std::ostream& operator << (std::ostream &, const BigGuys<U> &);
      template<class U> friend std::istream& operator >> (std::istream &, BigGuys<U> &);
      BigGuys<T> operator+ (BigGuys<T> const &);
      BigGuys<T> operator- (BigGuys<T> const &);
      size_t get_cap() const;
      size_t get_len() const;

    private:
      void clear_insig();
      T* guy;
      size_t len;
      size_t cap;
};

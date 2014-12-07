#ifndef VERIHY_MATH_BIG_INT_H
#define VERIHY_MATH_BIG_INT_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>

namespace verihy{

namespace math{


class big_int{
  private:
    std::vector<int> _val;
    bool _negative;
    static const int _bit = 4;
    static const int _base = 10000;
    // return a pointer  if ok
    //  otherwise null
    //  str drop signs
    char* pre_trans(const char* str, bool& is_negative);
  public:
    explicit big_int():_negative(false){
        big_int(0); 
    }
    big_int(int val);
    big_int(const char* str);
    big_int(const std::string& str);
    big_int(const big_int& bint);
    big_int& operator= (const big_int& bint);
    big_int operator+ (const big_int& rhs);
    big_int operator- (const big_int& rhs);
    big_int operator* (const big_int& rhs);
    big_int operator/ (const big_int& rhs);
    big_int& operator+=(const big_int& rhs);
    big_int& operator-=(const big_int& rhs);
    big_int& operator*=(const big_int& rhs);
    big_int& operator/=(const big_int& rhs);

    friend std::ostream& operator<<(std::ostream& os, const big_int& rhs);

    bool operator<(const big_int& rhs);
    bool operator>(const big_int& rhs);
};

std::ostream& operator<< (std::ostream& os, const big_int& rhs);


}// namespace math

}// namespace verihy

#endif

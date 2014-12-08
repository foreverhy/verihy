#ifndef VERIHY_MATH_BIG_INT_H
#define VERIHY_MATH_BIG_INT_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>

namespace verihy{

namespace math{


//TODO
// move constructor
// move assignment operator
// move +-*/ operator
class big_int{
  private:
    int _positive;
    std::vector<int> _val;
    // 1 positive
    // 0 zero
    // -1 negative
    static const int _bit = 4;
    static const int _base = 10000;
    static const int _visual_base = 10;
    // return a pointer  if ok
    //  otherwise null
    //  str drop signs
    static char* _pre_trans(const char* str, int& positive);
    int _ctoi(char ch){
        return ch - '0';
    }
    int _weight(int order){
        int tmp = 1;
        for(int i = 0; i < order; ++i){
            tmp *= _visual_base;
        }
        return tmp;
    }
    void _set_zero(){
        _val.clear();
        _val.push_back(0);
        _positive = 0;
    }

    void _fix_pre_zeros(){
        while(!_val.empty() && *(_val.rbegin()) == 0){
            _val.pop_back();
        }
        if(_val.empty())_val.push_back(0);
    }
  public:
    explicit big_int():_positive(0){
        big_int(0); 
    }
    big_int(int val);
    big_int(const char* str);
    big_int(const std::string &str);
    big_int(const big_int &bint);
    big_int(big_int &&rhs)noexcept;
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
    friend class debug;

    bool operator<(const big_int& rhs)const;
    bool operator>(const big_int& rhs)const;
    bool operator==(const big_int& rhs)const;
    bool operator<=(const big_int& rhs)const;
    bool operator>=(const big_int& rhs)const;

};

std::ostream& operator<< (std::ostream& os, const big_int& rhs);


}// namespace math

}// namespace verihy

#endif

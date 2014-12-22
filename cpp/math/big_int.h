#ifndef VERIHY_MATH_BIG_INT_H
#define VERIHY_MATH_BIG_INT_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

namespace verihy{

namespace math{


// TODO use unsigned 32/16 bit instead of int in vector _val
// TODO make operator +-*/ friend functions, but +=/-=/*=//= class member.
//  This is because we have 0 == big_int or 1 + big_int etc.
class big_int{
  private:
    int _positive;
    std::vector<int> _val;
    // 1 positive
    // 0 zero
    // -1 negative
    static const int _bit = 16;
    static const int _base = 65536;
    static const int _lowbits = 0xffff;
    static const int _visual_base = 10000;
    static const int _visual_bit = 4;
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
        //_val.push_back(0);
        _positive = 0;
    }

    void _fix_pre_zeros(){
        while(!_val.empty() && *(_val.rbegin()) == 0){
            _val.pop_back();
        }
        if(_val.empty())_positive=0;
    }

    // pure add , with same sign
    void add(const std::vector<int> &lhs, const std::vector<int> &rhs, std::vector<int> &ans);
    // pure sub, abs() of lhs is greater than rhs
    void sub(const std::vector<int> &lhs, const std::vector<int> &rhs, std::vector<int> &ans);

    int abs_compare(const big_int &rhs)const;

    

  public:
    template<typename Tin = int, typename Tout = int>
    static std::vector<Tout> trans_base(const std::vector<Tin> &in, int base_in, int base_out){
        std::vector<Tout> out;
        for(auto pin = in.crbegin(); pin != in.crend(); ++pin){
            int hi = *pin;
            for(auto pout = out.begin(); pout != out.end(); ++pout){
                int z = *pout * base_in + hi;
                hi = z / base_out;
                *pout = z % base_out;
            }
            while(hi){
                out.push_back(hi % base_out);
                hi /= base_out;
            }
        }
        return out;
    }

    big_int():big_int(0){}
    big_int(unsigned val);
    big_int(int val);
    big_int(const char* str);
    big_int(const std::string &str);
    big_int(const big_int &bint);
    big_int(big_int &&rhs)noexcept;
    big_int& operator= (big_int&& rhs)noexcept;
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

    ~big_int();

    void debug(){
        std::cout << *this << ": ";
        std::for_each(_val.begin(), _val.end(),[](const int x){std::cout << x << " ";});
        std::cout << std::endl;
    }
};

std::ostream& operator<< (std::ostream& os, const big_int& rhs);


}// namespace math

}// namespace verihy

#endif

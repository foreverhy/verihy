#ifndef VERIHY_MATH_BIG_INT_H
#define VERIHY_MATH_BIG_INT_H

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <algorithm>

namespace verihy{

namespace math{


// TODO use unsigned 32/16 bit instead of int in vector val_
// TODO make operator +-*/ friend functions, but +=/-=/*=//= class member.
//  This is because we have 0 == big_int or 1 + big_int etc.
class big_int{
  private:
    int positive_;
    std::vector<int> val_;
    // 1 positive
    // 0 zero
    // -1 negative
    static const int bit_ = 16;
    static const int base_ = 65536;
    static const int lowbits_ = 0xffff;
    static const int visual_base_ = 10000;
    static const int visual_bit_ = 4;
    // return a pointer  if ok
    //  otherwise null
    //  str drop signs
    static char* pre_trans_(const char* str, int& positive);
    int ctoi_(char ch){
        return ch - '0';
    }
    int weight_(int order){
        int tmp = 1;
        for(int i = 0; i < order; ++i){
            tmp *= visual_base_;
        }
        return tmp;
    }
    void set_zero_(){
        val_.clear();
        //val_.push_back(0);
        positive_ = 0;
    }

    void fix_pre_zeros_(){
        while(!val_.empty() && *(val_.rbegin()) == 0){
            val_.pop_back();
        }
        if(val_.empty())positive_=0;
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
        std::for_each(val_.begin(), val_.end(),[](const int x){std::cout << x << " ";});
        std::cout << std::endl;
    }
};

std::ostream& operator<< (std::ostream& os, const big_int& rhs);


}// namespace math

}// namespace verihy

#endif

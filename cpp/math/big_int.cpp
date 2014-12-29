#include "big_int.h"
#include <iomanip>
#include <cstring>
#include <cctype>
#include <iostream>
#include <algorithm>
#include <cassert>

#define VERIHY_DEBUG false

namespace verihy{
namespace math{

big_int::big_int(unsigned val):positive_(1){
    while(val){
        val_.push_back(val & lowbits_);
        val >>= bit_;
    }
    fix_pre_zeros_();
}

big_int::big_int(int val):positive_(0){
    auto lval = static_cast<long long>(val);
    if(lval > 0){
        positive_ = 1;
    }else if(lval < 0){
        lval = -lval;
        positive_ = -1;
    }else{
        val_.push_back(0);
        positive_ = 0;
    }

    while(lval){
        val_.push_back(lval % base_);
        lval /= base_;
    }
    fix_pre_zeros_();
}

big_int::big_int(big_int &&rhs)noexcept:positive_(rhs.positive_),val_(rhs.val_){}


big_int::big_int(const big_int& rhs):positive_(rhs.positive_),val_(rhs.val_){
}

big_int::big_int(const std::string& str):big_int(str.c_str()){
}

big_int::big_int(const char* str_):positive_(0){
    char* str = pre_trans_(str_, positive_);
    std::vector<char> tmp;
    for(char* pstr = str+std::strlen(str)-1; pstr>=str; --pstr){
        char ch = *pstr; 
        if(std::isdigit(ch)){
            tmp.push_back(ctoi_(ch));
        }else{
            set_zero_();
            return ;
        }
    }
    val_ = big_int::trans_base<char, int>(tmp, 10, base_);
    fix_pre_zeros_();
}

char* big_int::pre_trans_(const char* str_, int& positive){
    char* str = const_cast<char*>(str_);
    if(nullptr == str){
        return nullptr;
    }
    int len = std::strlen(str);
    if(0 == len){
        positive = 0;
        return nullptr;
    }
    if('-' == str[0]){
        positive = -1;
        return str + 1;
    }
    if('+' == str[0]){
        positive = 1;
        return str + 1;
    }
    positive = 1;
    return str;

}


std::ostream& operator<<(std::ostream& os, const big_int& rhs){
    if(rhs.positive_ == 0){
        os << "0";
        return os;
    }
    auto out = big_int::trans_base(rhs.val_, rhs.base_, rhs.visual_base_);
    if(rhs.positive_ < 0){
        os << "-";
    }
    bool is_first = true;
    for(auto part = out.crbegin(); part != out.crend(); ++part){
        if(!is_first){
            os << std::setw(rhs.visual_bit_) <<  std::setfill('0') << *part;
        }else{
            os << *part;
            is_first = false;
        }
    }

    return os;
}

big_int& big_int::operator=(const big_int& rhs){
    if(&rhs == this){
        return *this;
    }
    positive_ = rhs.positive_;
    val_ = rhs.val_;
    return *this;
}

big_int& big_int::operator=(big_int &&rhs)noexcept{
    if(&rhs == this){
        return *this;
    }
    positive_ = rhs.positive_;
    val_ = rhs.val_;
    return *this;
}

bool big_int::operator<(const big_int& rhs)const{
    // signs
    if(positive_ != rhs.positive_){
        return positive_ < rhs.positive_;
    }else if(!positive_){
        return false;
    }
    int flag = abs_compare(rhs);
    return positive_?flag<0:flag>0;
}

bool big_int::operator>(const big_int& rhs)const{
    return rhs.operator<(*this);
}

bool big_int::operator==(const big_int& rhs)const{
    if(positive_ != rhs.positive_){
        return false;
    }
    int flag = abs_compare(rhs);
    return flag == 0;
}

big_int::~big_int(){
}


// operators

big_int big_int::operator+(const big_int& rhs){
    big_int ans = 0;
    if(positive_ * rhs.positive_ >= 0){
        if(positive_ * rhs.positive_ == 0){
            ans.positive_ = positive_ + rhs.positive_;
        }else{
            ans.positive_ = positive_;
        }
        add(val_, rhs.val_, ans.val_);
    }else{
        int flag = abs_compare(rhs);
        if(flag > 0){
            sub(val_, rhs.val_, ans.val_);
            ans.positive_ = positive_;
        }else{
            sub(rhs.val_, val_, ans.val_);
            ans.positive_ = -positive_;
        }
    }

    ans.fix_pre_zeros_();
    return ans;
}

big_int big_int::operator-(const big_int& rhs){
    big_int ans = 0;
    if(positive_ * rhs.positive_ == 0){
        ans.val_ = positive_?val_:rhs.val_; 
        ans.positive_ = positive_?positive_:rhs.positive_;
    }else if (positive_ * rhs.positive_ > 0){
        int flag = abs_compare(rhs);
        if(flag > 0){
            sub(val_, rhs.val_, ans.val_);
            ans.positive_ = positive_;
        }else{
            sub(rhs.val_, val_, ans.val_);
            ans.positive_ = -positive_;
        }
    }else{
        add(val_, rhs.val_, ans.val_);
        ans.positive_ = positive_;
    }
    ans.fix_pre_zeros_();
    return ans;
}

int big_int::abs_compare(const big_int &rhs)const{
    auto lenl = val_.size(), lenr = rhs.val_.size();
    if(lenl != lenr){
        return lenl>lenr?1:-1;
    }
    for(auto pl = val_.crbegin(), pr = rhs.val_.crbegin();
            pl!=val_.crend(); ++pl, ++pr){
        if(*pl != *pr){
            return *pl > *pr?1:-1;
        }
    }
    return 0;
}


void big_int::add(const std::vector<int> &lhs, const std::vector<int> &rhs, std::vector<int> &ans){
    ans.clear();
    auto pl = lhs.begin();
    auto pr = rhs.begin();
    int carry = 0;
    for(; pl!=lhs.end() && pr!=rhs.end(); ++pl, ++pr){
        int tmp = (*pl + *pr) + carry;
        ans.push_back(tmp & lowbits_);
        if(tmp > lowbits_){
            carry = 1;
        }else{
            carry = 0;
        }
    }
    auto plr = pl, pend = lhs.end();
    if(plr == pend){
        plr = pr;
        pend = rhs.end();
    }
    for(; plr != pend; ++plr){
        int tmp = (*plr) + carry;
        ans.push_back(tmp & lowbits_);
        if(tmp > lowbits_){
            carry = 1;
        }else{
            carry = 0;
        }
    }
    if(carry){
        ans.push_back(carry);
    }
     
}

//gurantee that lhs is greater than or equal to rhs
void big_int::sub(const std::vector<int> &lhs, const std::vector<int> &rhs, std::vector<int> &ans){
    ans.clear();
    auto pl = lhs.begin();
    auto pr = rhs.begin();
    int borrow = 0;
    for(; pl!=lhs.end() && pr!=rhs.end(); ++pl, ++pr){
        int tmp = (*pl - *pr) - borrow;
        if(tmp < 0){
            tmp += base_;
            borrow = 1;
        }else{
            borrow = 0;
        }
        ans.push_back(tmp);
    }
    for(; pl != lhs.end(); ++pl){
        int tmp = (*pl) - borrow;
        if(tmp < 0){
            tmp += base_;
            borrow = 1;
        }else{
            borrow = 0;
        }
        ans.push_back(tmp);
    }
}

//TODO move extra operations, eg: add leading zeros, extra copy constructors
big_int big_int::operator*(const big_int&rhs){
    if(*this == 0|| rhs == 0){
        return big_int(0);
    }
    auto max_len = std::max(val_.size(), rhs.val_.size());
    if(max_len == 1){
        return big_int(static_cast<unsigned>(val_[0]) * static_cast<unsigned>(rhs.val_[0]));
    }

    auto val = val_, rhs_val = rhs.val_;
    val.insert(val.end(), max_len - val.size(), 0);
    rhs_val.insert(rhs_val.end(), max_len - rhs_val.size(), 0);
    auto mid = max_len >> 1;
    big_int x[2], y[2];
    x[0].val_.insert(x[0].val_.end(), val.begin(), val.begin()+mid);
    x[1].val_.insert(x[1].val_.end(), val.begin()+mid, val.end());
    y[0].val_.insert(y[0].val_.end(), rhs_val.begin(), rhs_val.begin()+mid);
    y[1].val_.insert(y[1].val_.end(), rhs_val.begin()+mid, rhs_val.end());
    x[0].positive_ = x[1].positive_ = y[0].positive_ = y[1].positive_ = 1;
    big_int z2 = x[1]*y[1];
    big_int z1 = x[1]*y[0] + x[0]*y[1];
    big_int ans = big_int(x[0]*y[0]);

    if(ans.val_.size() < mid){
        ans.val_.insert(ans.val_.end(), mid-ans.val_.size(), 0);
    }

    std::vector<int>::size_type pos_ans, pos_z;
    int carry = 0;
    for(pos_ans = mid, pos_z = 0; pos_ans < ans.val_.size() && pos_z < z1.val_.size(); ++pos_ans,++pos_z){
        auto tmp = ans.val_[pos_ans] + z1.val_[pos_z] + carry;
        ans.val_[pos_ans] = tmp & lowbits_;
        if(tmp > lowbits_){
            carry = 1;
        }else{
            carry = 0;
        }
    }
    if(pos_ans < ans.val_.size()){
        for(;pos_ans < ans.val_.size(); ++pos_ans){
            auto tmp = ans.val_[pos_ans] + carry;
            ans.val_[pos_ans] = tmp & lowbits_;
            if(tmp > lowbits_){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }else if(pos_z < z1.val_.size()){
        for(;pos_z < z1.val_.size(); ++pos_z){
            auto tmp = z1.val_[pos_z] + carry;
            ans.val_.push_back(tmp & lowbits_);
            if(tmp > lowbits_){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }
    if(carry){
        ans.val_.push_back(carry);
    }


    //ans.val_.insert(ans.val_.end(), z1.val_.begin(), z1.val_.end());

    if(ans.val_.size() < (mid<<1) ){
        ans.val_.insert(ans.val_.end(), (mid<<1)-ans.val_.size(), 0);
    }


    carry = 0;
    for(pos_ans = mid<<1, pos_z = 0; pos_ans < ans.val_.size() && pos_z < z2.val_.size(); ++pos_ans,++pos_z){
        auto tmp = ans.val_[pos_ans] + z2.val_[pos_z] + carry;
        ans.val_[pos_ans] = tmp & lowbits_;
        if(tmp > lowbits_){
            carry = 1;
        }else{
            carry = 0;
        }
    }
    if(pos_ans < ans.val_.size()){
        for(;pos_ans < ans.val_.size(); ++pos_ans){
            auto tmp = ans.val_[pos_ans] + carry;
            ans.val_[pos_ans] = tmp & lowbits_;
            if(tmp > lowbits_){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }else if(pos_z < z2.val_.size()){
        for(;pos_z < z2.val_.size(); ++pos_z){
            auto tmp = z2.val_[pos_z] + carry;
            ans.val_.push_back(tmp & lowbits_);
            if(tmp > lowbits_){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }
    if(carry){
        ans.val_.push_back(carry);
    }



    //ans.val_.insert(ans.val_.end(), z2.val_.begin(), z2.val_.end());
    ans.positive_ = positive_ * rhs.positive_;
    ans.fix_pre_zeros_();
    return ans;
}


}// namespace math

}// namespace verihy

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

big_int::big_int(unsigned val):_positive(1){
    while(val){
        _val.push_back(val & _lowbits);
        val >>= _bit;
    }
    _fix_pre_zeros();
}

big_int::big_int(int val):_positive(0){
    auto lval = static_cast<long long>(val);
    if(lval > 0){
        _positive = 1;
    }else if(lval < 0){
        lval = -lval;
        _positive = -1;
    }else{
        _val.push_back(0);
        _positive = 0;
    }

    while(lval){
        _val.push_back(lval % _base);
        lval /= _base;
    }
    _fix_pre_zeros();
}

big_int::big_int(big_int &&rhs)noexcept:_positive(rhs._positive),_val(rhs._val){}


big_int::big_int(const big_int& rhs):_positive(rhs._positive),_val(rhs._val){
}

big_int::big_int(const std::string& str):big_int(str.c_str()){
}

big_int::big_int(const char* _str):_positive(0){
    char* str = _pre_trans(_str, _positive);
    std::vector<char> tmp;
    for(char* pstr = str+std::strlen(str)-1; pstr>=str; --pstr){
        char ch = *pstr; 
        if(std::isdigit(ch)){
            tmp.push_back(_ctoi(ch));
        }else{
            _set_zero();
            return ;
        }
    }
    _val = big_int::trans_base<char, int>(tmp, 10, _base);
    _fix_pre_zeros();
}

char* big_int::_pre_trans(const char* _str, int& positive){
    char* str = const_cast<char*>(_str);
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
    if(rhs._positive == 0){
        os << "0";
        return os;
    }
    auto out = big_int::trans_base(rhs._val, rhs._base, rhs._visual_base);
    if(rhs._positive < 0){
        os << "-";
    }
    bool is_first = true;
    for(auto part = out.crbegin(); part != out.crend(); ++part){
        if(!is_first){
            os << std::setw(rhs._visual_bit) <<  std::setfill('0') << *part;
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
    _positive = rhs._positive;
    _val = rhs._val;
    return *this;
}

big_int& big_int::operator=(big_int &&rhs)noexcept{
    if(&rhs == this){
        return *this;
    }
    _positive = rhs._positive;
    _val = rhs._val;
    return *this;
}

bool big_int::operator<(const big_int& rhs)const{
    // signs
    if(_positive != rhs._positive){
        return _positive < rhs._positive;
    }else if(!_positive){
        return false;
    }
    int flag = abs_compare(rhs);
    return _positive?flag<0:flag>0;
}

bool big_int::operator>(const big_int& rhs)const{
    return rhs.operator<(*this);
}

bool big_int::operator==(const big_int& rhs)const{
    if(_positive != rhs._positive){
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
    if(_positive * rhs._positive >= 0){
        if(_positive * rhs._positive == 0){
            ans._positive = _positive + rhs._positive;
        }else{
            ans._positive = _positive;
        }
        add(_val, rhs._val, ans._val);
    }else{
        int flag = abs_compare(rhs);
        if(flag > 0){
            sub(_val, rhs._val, ans._val);
            ans._positive = _positive;
        }else{
            sub(rhs._val, _val, ans._val);
            ans._positive = -_positive;
        }
    }

    ans._fix_pre_zeros();
    return ans;
}

big_int big_int::operator-(const big_int& rhs){
    big_int ans = 0;
    if(_positive * rhs._positive == 0){
        ans._val = _positive?_val:rhs._val; 
        ans._positive = _positive?_positive:rhs._positive;
    }else if (_positive * rhs._positive > 0){
        int flag = abs_compare(rhs);
        if(flag > 0){
            sub(_val, rhs._val, ans._val);
            ans._positive = _positive;
        }else{
            sub(rhs._val, _val, ans._val);
            ans._positive = -_positive;
        }
    }else{
        add(_val, rhs._val, ans._val);
        ans._positive = _positive;
    }
    ans._fix_pre_zeros();
    return ans;
}

int big_int::abs_compare(const big_int &rhs)const{
    auto lenl = _val.size(), lenr = rhs._val.size();
    if(lenl != lenr){
        return lenl>lenr?1:-1;
    }
    for(auto pl = _val.crbegin(), pr = rhs._val.crbegin();
            pl!=_val.crend(); ++pl, ++pr){
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
        ans.push_back(tmp & _lowbits);
        if(tmp > _lowbits){
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
        ans.push_back(tmp & _lowbits);
        if(tmp > _lowbits){
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
            tmp += _base;
            borrow = 1;
        }else{
            borrow = 0;
        }
        ans.push_back(tmp);
    }
    for(; pl != lhs.end(); ++pl){
        int tmp = (*pl) - borrow;
        if(tmp < 0){
            tmp += _base;
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
    auto max_len = std::max(_val.size(), rhs._val.size());
    if(max_len == 1){
        return big_int(static_cast<unsigned>(_val[0]) * static_cast<unsigned>(rhs._val[0]));
    }

    auto val = _val, rhs_val = rhs._val;
    val.insert(val.end(), max_len - val.size(), 0);
    rhs_val.insert(rhs_val.end(), max_len - rhs_val.size(), 0);
    auto mid = max_len >> 1;
    big_int x[2], y[2];
    x[0]._val.insert(x[0]._val.end(), val.begin(), val.begin()+mid);
    x[1]._val.insert(x[1]._val.end(), val.begin()+mid, val.end());
    y[0]._val.insert(y[0]._val.end(), rhs_val.begin(), rhs_val.begin()+mid);
    y[1]._val.insert(y[1]._val.end(), rhs_val.begin()+mid, rhs_val.end());
    x[0]._positive = x[1]._positive = y[0]._positive = y[1]._positive = 1;
    big_int z2 = x[1]*y[1];
    big_int z1 = x[1]*y[0] + x[0]*y[1];
    big_int ans = big_int(x[0]*y[0]);

    if(ans._val.size() < mid){
        ans._val.insert(ans._val.end(), mid-ans._val.size(), 0);
    }

    std::vector<int>::size_type pos_ans, pos_z;
    int carry = 0;
    for(pos_ans = mid, pos_z = 0; pos_ans < ans._val.size() && pos_z < z1._val.size(); ++pos_ans,++pos_z){
        auto tmp = ans._val[pos_ans] + z1._val[pos_z] + carry;
        ans._val[pos_ans] = tmp & _lowbits;
        if(tmp > _lowbits){
            carry = 1;
        }else{
            carry = 0;
        }
    }
    if(pos_ans < ans._val.size()){
        for(;pos_ans < ans._val.size(); ++pos_ans){
            auto tmp = ans._val[pos_ans] + carry;
            ans._val[pos_ans] = tmp & _lowbits;
            if(tmp > _lowbits){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }else if(pos_z < z1._val.size()){
        for(;pos_z < z1._val.size(); ++pos_z){
            auto tmp = z1._val[pos_z] + carry;
            ans._val.push_back(tmp & _lowbits);
            if(tmp > _lowbits){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }
    if(carry){
        ans._val.push_back(carry);
    }


    //ans._val.insert(ans._val.end(), z1._val.begin(), z1._val.end());

    if(ans._val.size() < (mid<<1) ){
        ans._val.insert(ans._val.end(), (mid<<1)-ans._val.size(), 0);
    }


    carry = 0;
    for(pos_ans = mid<<1, pos_z = 0; pos_ans < ans._val.size() && pos_z < z2._val.size(); ++pos_ans,++pos_z){
        auto tmp = ans._val[pos_ans] + z2._val[pos_z] + carry;
        ans._val[pos_ans] = tmp & _lowbits;
        if(tmp > _lowbits){
            carry = 1;
        }else{
            carry = 0;
        }
    }
    if(pos_ans < ans._val.size()){
        for(;pos_ans < ans._val.size(); ++pos_ans){
            auto tmp = ans._val[pos_ans] + carry;
            ans._val[pos_ans] = tmp & _lowbits;
            if(tmp > _lowbits){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }else if(pos_z < z2._val.size()){
        for(;pos_z < z2._val.size(); ++pos_z){
            auto tmp = z2._val[pos_z] + carry;
            ans._val.push_back(tmp & _lowbits);
            if(tmp > _lowbits){
                carry = 1;
            }else{
                carry = 0;
            }
        }
    }
    if(carry){
        ans._val.push_back(carry);
    }



    //ans._val.insert(ans._val.end(), z2._val.begin(), z2._val.end());
    ans._positive = _positive * rhs._positive;
    ans._fix_pre_zeros();
    return ans;
}


}// namespace math

}// namespace verihy

#ifndef VERIHY_VSTD_VECTOR_HPP
#define VERIHY_VSTD_VECTOR_HPP

#include <cstdint>
#include <memory>

namespace verihy{

namespace vstd{

template<typename T_>
class Vector{
  public:
    typedef std::uint32_t size_type;
    typedef T_ value_type;
    typedef std::allocator<T_> alloc_type;
    typedef T_& reference;
    typedef T_* pointer;
    typedef Vector<T_> self_type;
    class iterator;
  private:
    pointer data_;
    size_type size_;
    size_type capacity_;
    static alloc_type alloc_;
    static const size_type growsize_ = 24;

    void grow(){
        auto ptr = alloc_.allocate(capacity_ + growsize_);
        //TODO if capacity > UINT32_MAX, throw exception
        if(size_){
            for(size_type i = 0; i < size_; ++i){
                //TODO template specialized for int,char....
                // we don't need destructor for these build-in types
                //  also don't need move constructor
                alloc_.construct(ptr + i, std::move(*(data_ +i)));
                alloc_.destroy(data_ + i);
            }
            alloc_.deallocate(data_, capacity_);
        }
        capacity_ += growsize_;
        data_ = ptr;
    }

  public:

    Vector():data_(nullptr), size_(0), capacity_(0){};
    Vector(std::initializer_list<value_type>);
    ~Vector(){
        for(size_type i = 0; i < size_; ++i){
            alloc_.destroy(data_ + i);
        }
        alloc_.deallocate(data_, capacity_);
    }

    Vector(const Vector &rhs):size_(rhs.size_), capacity_(rhs.size_){
        auto ptr = alloc_.allocate(capacity_);
        data_ = ptr;
        auto prhs = rhs.data_;
        for(size_type i = 0; i < size_; ++i){
            alloc_.construct(ptr++, *(prhs++));
        }
    }

    Vector(Vector &&rhs):data_(rhs.data_), size_(rhs.size_), capacity_(rhs.capacity_){
        rhs.data_ = nullptr; 
        rhs.size_ = rhs.capacity_ = 0;
    }

    void push_back(const value_type &x){
        if(size_ == capacity_){
            grow();
        }
        alloc_.construct(data_ + size_, x);
        ++size_;
    }

    void push_back(value_type &&x){
        if(size_ == capacity_){
            grow();
        }
        alloc_.construct(data_ + size_, std::move(x));
        ++size_;
    }

    reference operator[](size_type offset){
        return *(data_ + offset);
    }

    size_type size(){
        return size_;
    }

    self_type& operator=(const self_type &rhs){
        if(&rhs == this){
            return *this;
        }
        auto ptr = data_;
        for(size_type i = 0; i < size_; ++i){
            alloc_.destroy(ptr++);
        }
        alloc_.deallocate(data_, size_);

        size_ = rhs.size_;
        capacity_ = size_;

        ptr = alloc_.allocate(capacity_);
        data_ = ptr;
        auto prhs = rhs.data_;
        for(size_type i = 0; i < size_; ++i){
            alloc_.construct(ptr++, *(prhs++));
        }
        return *this;
    }

    self_type& operator=(self_type &&rhs){
        if(&rhs == this){
            return *this;
        }
        data_ = rhs.data_;
        size_ = rhs.size_;
        capacity_ = rhs.capacity_;
        rhs.data_ = nullptr;
        rhs.size_ = rhs.capacity_ = 0;
        return *this;
    }


    //iterators
    iterator begin(){
        return iterator(data_);
    }

    iterator end(){
        return iterator(data_ + size_);
    }


    class iterator{
      public:
        typedef std::uint32_t size_type;
        typedef T_ value_type;
        typedef T_* pointer;
        typedef T_& reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::int32_t difference_type;
      private:
        pointer ptr_;
      public:
        iterator(pointer ptr):ptr_(ptr){}
        iterator():ptr_(nullptr){}
        iterator(const iterator &rhs):ptr_(rhs.ptr_){ }

        reference operator*(){
            return *ptr_;
        }
        pointer operator->(){
            return ptr_;
        }

        iterator& operator++(){
            ++ptr_;
            return *this;
        }

        iterator operator++(int ){
            auto ptr = ptr_;
            ++ptr_; 
            return iterator(ptr);
        }

        iterator& operator--(){
            --ptr_;
            return *this;
        }

        iterator operator--(int ){
            auto ptr = ptr_;
            --ptr_;
            return iterator(ptr);
        }

        iterator& operator=(const iterator &rhs){
            ptr_ = rhs.ptr_;
            return *this;
        }

        iterator& operator+=(const size_type &rhs){
            ptr_ += rhs;
            return *this;
        }

        iterator& operator-=(const size_type &rhs){
            ptr_ -= rhs;
            return *this;
        }

        bool operator<(const iterator &rhs){
            return ptr_ < rhs.ptr_;
        }
        bool operator>(const iterator &rhs){
            return ptr_ > rhs.ptr_;
        }
        bool operator==(const iterator &rhs){
            return ptr_ == rhs.ptr_;
        }
        bool operator!=(const iterator &rhs){
            return ptr_ != rhs.ptr_;
        }
        bool operator<=(const iterator &rhs){
            return ptr_ <= rhs.ptr_;
        }
        bool operator>=(const iterator &rhs){
            return ptr_ >= rhs.ptr_;
        }

        iterator operator+(const size_type &rhs){
            auto it = *this;
            it += rhs;
            return it;
        }

        iterator operator-(const size_type &rhs){
            auto it = *this;
            it -= rhs;
            return it;
        }

        difference_type operator-(const iterator &rhs){
            return ptr_ - rhs.ptr_;
        }

    };// class Vector::iterator
    

};//class Vector

template<typename T_>
typename Vector<T_>::alloc_type Vector<T_>::alloc_;


template<>
void Vector<int>::grow(){
    auto ptr = alloc_.allocate(capacity_ + growsize_);
    //TODO if capacity > UINT32_MAX, throw exception
    if(size_){
        std::uninitialized_copy_n(iterator(data_), size_, iterator(ptr));
    }
    capacity_ += growsize_;
    data_ = ptr;
}// Vector<int>::grow()

}
    
}

#endif

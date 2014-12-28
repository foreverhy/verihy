#ifndef VERIHY_VSTD_VECTOR_HPP
#define VERIHY_VSTD_VECTOR_HPP

#include <cstdint>
#include <memory>

namespace verihy{

namespace vstd{

template<typename _T>
class Vector{
  public:
    typedef std::uint32_t size_type;
    typedef _T value_type;
    typedef std::allocator<_T> alloc_type;
    typedef _T& reference;
    typedef _T* pointer;
    typedef Vector<_T> self_type;
    class iterator;
  private:
    pointer _data;
    size_type _size;
    size_type _capacity;
    static alloc_type _alloc;
    static const size_type _growsize = 24;

    void grow(){
        auto ptr = _alloc.allocate(_capacity + _growsize);
        //TODO if capacity > UINT32_MAX, throw exception
        if(_size){
            for(size_type i = 0; i < _size; ++i){
                //TODO template specialized for int,char....
                // we don't need destructor for these build-in types
                //  also don't need move constructor
                _alloc.construct(ptr + i, std::move(*(_data +i)));
                _alloc.destroy(_data + i);
            }
            _alloc.deallocate(_data, _capacity);
        }
        _capacity += _growsize;
        _data = ptr;
    }

  public:

    Vector():_data(nullptr), _size(0), _capacity(0){};
    Vector(std::initializer_list<value_type>);
    ~Vector(){
        for(size_type i = 0; i < _size; ++i){
            _alloc.destroy(_data + i);
        }
        _alloc.deallocate(_data, _capacity);
    }

    Vector(const Vector &rhs):_size(rhs._size), _capacity(rhs._size){
        auto ptr = _alloc.allocate(_capacity);
        _data = ptr;
        auto prhs = rhs._data;
        for(size_type i = 0; i < _size; ++i){
            _alloc.construct(ptr++, *(prhs++));
        }
    }

    Vector(Vector &&rhs):_data(rhs._data), _size(rhs._size), _capacity(rhs._capacity){
        rhs._data = nullptr; 
        rhs._size = rhs._capacity = 0;
    }

    void push_back(const value_type &x){
        if(_size == _capacity){
            grow();
        }
        _alloc.construct(_data + _size, x);
        ++_size;
    }

    void push_back(value_type &&x){
        if(_size == _capacity){
            grow();
        }
        _alloc.construct(_data + _size, std::move(x));
        ++_size;
    }

    reference operator[](size_type offset){
        return *(_data + offset);
    }

    size_type size(){
        return _size;
    }

    self_type& operator=(const self_type &rhs){
        if(&rhs == this){
            return *this;
        }
        auto ptr = _data;
        for(size_type i = 0; i < _size; ++i){
            _alloc.destroy(ptr++);
        }
        _alloc.deallocate(_data, _size);

        _size = rhs._size;
        _capacity = _size;

        ptr = _alloc.allocate(_capacity);
        _data = ptr;
        auto prhs = rhs._data;
        for(size_type i = 0; i < _size; ++i){
            _alloc.construct(ptr++, *(prhs++));
        }
        return *this;
    }

    self_type& operator=(self_type &&rhs){
        if(&rhs == this){
            return *this;
        }
        _data = rhs._data;
        _size = rhs._size;
        _capacity = rhs._capacity;
        rhs._data = nullptr;
        rhs._size = rhs._capacity = 0;
        return *this;
    }


    //iterators
    iterator begin(){
        return iterator(_data);
    }

    iterator end(){
        return iterator(_data + _size);
    }


    class iterator{
      public:
        typedef std::uint32_t size_type;
        typedef _T value_type;
        typedef _T* pointer;
        typedef _T& reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::int32_t difference_type;
      private:
        pointer _ptr;
      public:
        iterator(pointer ptr):_ptr(ptr){}
        iterator():_ptr(nullptr){}
        iterator(const iterator &rhs):_ptr(rhs._ptr){ }

        reference operator*(){
            return *_ptr;
        }
        pointer operator->(){
            return _ptr;
        }

        iterator& operator++(){
            ++_ptr;
            return *this;
        }

        iterator operator++(int ){
            auto ptr = _ptr;
            ++_ptr; 
            return iterator(ptr);
        }

        iterator& operator--(){
            --_ptr;
            return *this;
        }

        iterator operator--(int ){
            auto ptr = _ptr;
            --_ptr;
            return iterator(ptr);
        }

        iterator& operator=(const iterator &rhs){
            _ptr = rhs._ptr;
            return *this;
        }

        iterator& operator+=(const size_type &rhs){
            _ptr += rhs;
            return *this;
        }

        iterator& operator-=(const size_type &rhs){
            _ptr -= rhs;
            return *this;
        }

        bool operator<(const iterator &rhs){
            return _ptr < rhs._ptr;
        }
        bool operator>(const iterator &rhs){
            return _ptr > rhs._ptr;
        }
        bool operator==(const iterator &rhs){
            return _ptr == rhs._ptr;
        }
        bool operator!=(const iterator &rhs){
            return _ptr != rhs._ptr;
        }
        bool operator<=(const iterator &rhs){
            return _ptr <= rhs._ptr;
        }
        bool operator>=(const iterator &rhs){
            return _ptr >= rhs._ptr;
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
            return _ptr - rhs._ptr;
        }

    };// class Vector::iterator
    

};//class Vector

template<typename _T>
typename Vector<_T>::alloc_type Vector<_T>::_alloc;

}
    
}

#endif

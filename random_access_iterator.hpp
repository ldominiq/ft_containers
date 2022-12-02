//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    template< typename T >
    class random_access_iterator {
    public:
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef random_access_iterator_tag      iterator_category;

    protected:
        pointer _ptr;

    public:
        random_access_iterator() : _ptr(NULL) {};
        random_access_iterator(pointer ptr) : _ptr(ptr) {};
        ~random_access_iterator() {};

        random_access_iterator(const random_access_iterator &other) {
            *this = other;
        }

        random_access_iterator &operator=(const random_access_iterator &rhs) {
            this->_ptr = rhs._ptr;
            return (*this);
        }

        bool                        operator==(const random_access_iterator& other) const {
            return (_ptr == other._ptr);
        }
        bool                        operator!=(const random_access_iterator& other)const {
            return (_ptr != other._ptr);
        }

        random_access_iterator&     operator+=(const difference_type& movement) {
            _ptr += movement;
            return (*this);
        }
        random_access_iterator&     operator-=(const difference_type& movement) {
            _ptr -= movement;
            return (*this);
        }
        random_access_iterator&     operator++() {
            ++_ptr;
            return (*this);
        }
        random_access_iterator&     operator--() {
            --_ptr;
            return (*this);
        }
        random_access_iterator      operator++(int) {
            random_access_iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        random_access_iterator      operator--(int) {
            random_access_iterator tmp(*this);
            --(*this);
            return tmp;
        }
        random_access_iterator      operator+(const difference_type& movement) {
            pointer oldPtr = _ptr;
            _ptr+=movement;
            random_access_iterator tmp(*this);
            _ptr = oldPtr;
            return tmp;
        }
        random_access_iterator      operator-(const difference_type& movement) {
            pointer oldPtr = _ptr;
            _ptr-=movement;
            random_access_iterator tmp(*this);
            _ptr = oldPtr;
            return tmp;
        }

        difference_type             operator-(const random_access_iterator& iter) {
            return ft::iterator<random_access_iterator_tag, T>::difference_type(iter.getPtr(), this->getPtr());
        }

        reference                   operator*(){ return *_ptr; }
        pointer                     operator->(){ return _ptr; }

        reference operator[](int index) { return _ptr[index]; }
        reference operator[](int index) const { return _ptr[index]; }

        operator random_access_iterator<const T>() const {
            return (random_access_iterator<const T>(this->_ptr));
        }

    }; // class random_access_iterator
} // namespace ft


#endif //FT_RANDOM_ACCESS_ITERATOR_HPP

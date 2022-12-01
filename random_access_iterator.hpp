//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    template< class T>
    class random_access_iterator : public ft::iterator< ft::random_access_iterator_tag, T > {
    public:
        typedef typename ft::iterator< ft::random_access_iterator_tag, T >::difference_type      difference_type;
        typedef typename ft::iterator< ft::random_access_iterator_tag, T >::value_type           value_type;
        typedef typename ft::iterator< ft::random_access_iterator_tag, T >::pointer              pointer;
        typedef typename ft::iterator< ft::random_access_iterator_tag, T >::reference            reference;
        typedef typename ft::iterator< ft::random_access_iterator_tag, T >::iterator_category    iterator_category;

    protected:
        pointer _ptr;

    public:
        random_access_iterator() : _ptr(NULL) {};
        random_access_iterator(const random_access_iterator< T >& other) : _ptr(other._ptr) {};
        ~random_access_iterator() {};

        random_access_iterator&     operator=(pointer* ptr) {
            _ptr = ptr;
            return (*this);
        }

        bool                        operator==(const random_access_iterator& iter)const {
            return (_ptr == iter.getConstPtr());
        }
        bool                        operator!=(const random_access_iterator& iter)const {
            return (_ptr != iter.getConstPtr());
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
            ++_ptr;
            return tmp;
        }
        random_access_iterator      operator--(int) {
            random_access_iterator tmp(*this);
            --_ptr;
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
        const reference             operator*()const{ return *_ptr; }
        pointer                     operator->(){ return _ptr; }

        pointer                     getPtr()const{ return _ptr; }
        const pointer               getConstPtr()const{ return _ptr; }

    }; // class random_access_iterator
} // namespace ft


#endif //FT_RANDOM_ACCESS_ITERATOR_HPP

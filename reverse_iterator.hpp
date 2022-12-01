//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_CONTAINERS_REVERSE_ITERATOR_HPP
#define FT_CONTAINERS_REVERSE_ITERATOR_HPP

#include "iterator.hpp"

/* ===========================================================================================================
 * REVERSE_ITERATOR
 * =========================================================================================================*/

template< class Iterator >
class reverse_iterator {
protected:
    Iterator _current;
    typedef ft::iterator_traits<Iterator>	traits_type;

public:
    typedef Iterator								iterator_type;
    typedef typename traits_type::iterator_category	iterator_category;
    typedef typename traits_type::value_type		value_type;
    typedef typename traits_type::difference_type	difference_type;
    typedef typename traits_type::pointer			pointer;
    typedef typename traits_type::reference			reference;

public:
    reverse_iterator() : _current(){}

    explicit reverse_iterator(iterator_type it) : _current(it){}

    template < class Iter >
    reverse_iterator(const reverse_iterator< Iter >& rev_it) : _current(rev_it.base()) {}

    virtual ~reverse_iterator(){};

    iterator_type base() const { return _current; }

    operator reverse_iterator< const Iterator >() const { return this->_current; }

    reference operator*() const {
        iterator_type tmp_iter = _current;
        return *(--tmp_iter);
    }

    reverse_iterator operator+(difference_type n) const {
        return reverse_iterator(_current - n);
    }
    reverse_iterator& operator++() {
        --_current;
        return *this;
    }
    reverse_iterator operator++(int) {
        reverse_iterator tmp = *this;
        --_current;
        return tmp;
    }
    reverse_iterator& operator+=(difference_type n) {
        _current -= n;
        return *this;
    }
    reverse_iterator operator-(difference_type n) const {
        return reverse_iterator(_current + n);
    }
    reverse_iterator& operator--() {
        ++_current;
        return *this;
    }
    reverse_iterator operator--(int) {
        reverse_iterator tmp = *this;
        ++_current;
        return tmp;
    }
    reverse_iterator& operator-=(difference_type n) {
        _current += n;
        return *this;
    }

    pointer operator->() const { return &(operator*()); };

    reference operator[](difference_type n) const { return (_current[-n - 1]); };
};


/* ===========================================================================================================
 * REVERSE_ITERATOR => NON-MEMBER FUNCTION OVERLOADS
 * =========================================================================================================*/

/* Relational operators== for reverse_iterator */
template < class Iterator1, class Iterator2 >
bool operator==(const reverse_iterator< Iterator1 >& lhs,
                const reverse_iterator< Iterator2 >& rhs) {
    return (lhs.base() == rhs.base());
}

/* Relational operators!= for reverse_iterator */
template < class Iterator1, class Iterator2 >
bool operator!=(const reverse_iterator< Iterator1 >& lhs,
                const reverse_iterator< Iterator2 >& rhs) {
    return (lhs.base() != rhs.base());
}

/* Relational operators< for reverse_iterator */
template < class Iterator1, class Iterator2 >
bool operator<(const reverse_iterator< Iterator1 >& lhs,
               const reverse_iterator< Iterator2 >& rhs) {
    return (lhs.base() > rhs.base());
}

/* Relational operators<= for reverse_iterator */
template < class Iterator1, class Iterator2 >
bool operator<=(const reverse_iterator< Iterator1 >& lhs,
                const reverse_iterator< Iterator2 >& rhs) {
    return (lhs.base() >= rhs.base());
}

/* Relational operators> for reverse_iterator */
template < class Iterator1, class Iterator2 >
bool operator>(const reverse_iterator< Iterator1 >& lhs,
               const reverse_iterator< Iterator2 >& rhs) {
    return (lhs.base() < rhs.base());
}

/* Relational operators>= for reverse_iterator */
template < class Iterator1, class Iterator2 >
bool operator>=(const reverse_iterator< Iterator1 >& lhs,
                const reverse_iterator< Iterator2 >& rhs) {
    return (lhs.base() <= rhs.base());
}

/**
 * Returns a reverse iterator pointing to the element located n positions
 * away from the element pointed to by rev_it.
 *
 * @param n  Number of elements to offset.
 * Member type difference_type is an alias of Iterator's own difference type.
 * @param rev_it Reverse iterator.
 */
template < class Iterator >
reverse_iterator< Iterator > operator+(
        typename reverse_iterator< Iterator >::difference_type n,
        const reverse_iterator< Iterator >& rev_it) {
    return rev_it + n;
}

/* Returns the distance between lhs and rhs. */
template < class Iterator1, class Iterator2 >
typename reverse_iterator< Iterator1 >::difference_type operator-(
        const reverse_iterator< Iterator1 >& lhs,
        const reverse_iterator< Iterator2 >& rhs) {
    return rhs.base() - lhs.base();
}

#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP

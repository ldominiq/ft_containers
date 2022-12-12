//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_REVERSE_ITERATOR_HPP
#define FT_REVERSE_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    /* ===========================================================================================================
     * REVERSE_ITERATOR => MEMBER FUNCTIONS
     * =========================================================================================================*/

    /**
     * This class reverses the direction in which a bidirectional or random-access iterator iterates through a range.
     * @tparam Iterator
     */
    template< typename Iterator >
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
        reverse_iterator(const iterator_type& it) : _current(it){}
        template< typename _Iter >
        reverse_iterator(const reverse_iterator<_Iter>& i) : _current(i.base()) {}

        iterator_type base() const { return _current; }

        reference           operator*() const	{ Iterator tmp = _current;	return *(--tmp); }
        pointer	            operator->() const { return &(operator*()); }
        reverse_iterator&   operator++() { --_current; return *this; }
        reverse_iterator    operator++(int) { reverse_iterator tmp = *this; --_current; return tmp; }
        reverse_iterator&   operator--() { ++_current; return *this; }
        reverse_iterator    operator--(int) { reverse_iterator tmp = *this; ++_current; return tmp; }
        reverse_iterator    operator+(difference_type n) const { return reverse_iterator(_current - n); }
        reverse_iterator&   operator+=(difference_type n) {	_current -= n; return *this; }
        reverse_iterator    operator-(difference_type n) const { return reverse_iterator(_current + n); }
        reverse_iterator&   operator-=(difference_type n) {	_current += n; return *this; }
        reference           operator[](difference_type n) const	{ return *(*this + n); }
        difference_type	    operator-(reverse_iterator const &rhs) const { return rhs._current - _current; }
    };


    /* ===========================================================================================================
     * REVERSE_ITERATOR => NON-MEMBER FUNCTION OVERLOADS
     * =========================================================================================================*/

    /* Relational operators== for reverse_iterator */
    template<typename _IteratorL, typename _IteratorR>
    bool operator==(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
    { return lhs.base() == rhs.base(); }

    template<typename _Iterator>
    bool operator==(const reverse_iterator<_Iterator>& lhs,	const reverse_iterator<_Iterator>& rhs)
    { return lhs.base() == rhs.base(); }

    /* Relational operators!= for reverse_iterator */
    template<typename _IteratorL, typename _IteratorR>
    bool operator!=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
    { return !(lhs.base() == rhs.base()); }

    template<typename _Iterator>
    bool operator!=(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs)
    { return !(lhs.base() == rhs.base()); }

    /* Relational operators< for reverse_iterator */
    template<typename _IteratorL, typename _IteratorR>
    bool operator<(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
    { return lhs.base() > rhs.base(); }

    template<typename _Iterator>
    bool operator<(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs)
    { return lhs.base() > rhs.base(); }

    /* Relational operators<= for reverse_iterator */
    template<typename _IteratorL, typename _IteratorR>
    bool operator<=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
    { return lhs.base() >= rhs.base(); }

    template<typename _Iterator>
    bool operator<=(const reverse_iterator<_Iterator>& lhs,	const reverse_iterator<_Iterator>& rhs)
    { return lhs.base() >= rhs.base(); }

    /* Relational operators> for reverse_iterator */
    template <class _Iterator_L, class _Iterator_R>
    bool operator> (const reverse_iterator<_Iterator_L>& lhs, const reverse_iterator<_Iterator_R>& rhs)
    { return lhs.base() < rhs.base(); }

    template <class _Iterator>
    bool operator>  (const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs)
    { return lhs.base() < rhs.base(); }

    /* Relational operators>= for reverse_iterator */
    template<typename _IteratorL, typename _IteratorR>
    bool operator>=(const reverse_iterator<_IteratorL>& lhs, const reverse_iterator<_IteratorR>& rhs)
    { return lhs.base() <= rhs.base(); }

    template<typename _Iterator>
    bool operator>=(const reverse_iterator<_Iterator>& lhs,	const reverse_iterator<_Iterator>& rhs)
    { return lhs.base() <= rhs.base(); }

    /**
     * @tparam _Iterator
     * @param lhs Number of elements to offset.
     * @param rhs Reverse iterator.
     * @return Returns a reverse iterator pointing to the element located n positions
     * away from the element pointed to by rev_it.
     */
    template< class _Iterator >
    reverse_iterator< _Iterator >
    operator+(const int &lhs,  const reverse_iterator< _Iterator > &rhs)
    { return rhs + lhs; }

    /* Returns the distance between lhs and rhs. */
    template <class _Iterator>
    typename reverse_iterator<_Iterator>::difference_type
    operator- (const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs)
    { return rhs - lhs; }
}

#endif //FT_CONTAINERS_REVERSE_ITERATOR_HPP

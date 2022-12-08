//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
#define FT_RANDOM_ACCESS_ITERATOR_HPP

#include "iterator.hpp"

namespace ft {

    template < typename Iterator >
    class random_access_iterator {
    protected:
        Iterator current;

    private:
        typedef iterator_traits< Iterator > traits_type;

    public:
        typedef Iterator									iterator_type;
        typedef typename traits_type::iterator_category		iterator_category;
        typedef typename traits_type::value_type			value_type;
        typedef typename traits_type::difference_type		difference_type;
        typedef typename traits_type::pointer				pointer;
        typedef typename traits_type::reference				reference;

    public:

        random_access_iterator() : current(Iterator()) {}
        random_access_iterator(const Iterator &start) : current(start) {}

        template< typename Iter >
        random_access_iterator(const random_access_iterator< Iter > &it) : current(it.base()) {}

        const Iterator base() const { return current; }

        reference               operator*() const {return *current;}
        pointer	                operator->() const { return &(operator*()); }
        random_access_iterator& operator++() { current++; return *this; }
        random_access_iterator  operator++(int) {random_access_iterator retval = *this; ++(*this); return retval; }
        random_access_iterator& operator--() { current--; return *this; }
        random_access_iterator  operator--(int) {random_access_iterator retval = *this; --(*this); return retval; }
        random_access_iterator  operator+(difference_type n) const { return random_access_iterator(current + n); }
        random_access_iterator& operator+=(difference_type n) {	current += n; return *this;	}
        random_access_iterator  operator-(difference_type n) const { return random_access_iterator(current - n); }
        random_access_iterator& operator-=(difference_type n) {	current -= n; return *this;	}
        reference               operator[](difference_type n) const	{ return *(*this + n); }
        bool                    operator==(const random_access_iterator other) const {return current == other.current;}
        bool                    operator!=(const random_access_iterator other) const {return !(*this == other);}

    }; // class random_access_iterator

    template< typename IteratorL, typename IteratorR >
    bool operator<(const random_access_iterator< IteratorL > &lhs,
                   const random_access_iterator< IteratorR > &rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template< typename IteratorL, typename IteratorR >
    bool operator>(const random_access_iterator< IteratorL > &lhs,
                   const random_access_iterator< IteratorR > &rhs)
    {
        return (rhs.base() < lhs.base());
    }

    template< typename IteratorL, typename IteratorR >
    bool operator>=(const random_access_iterator< IteratorL > &lhs,
                    const random_access_iterator< IteratorR > &rhs)
    {
        return !(lhs.base() < rhs.base());
    }

    template< typename IteratorL, typename IteratorR >
    bool operator<=(const random_access_iterator< IteratorL > &lhs,
                    const random_access_iterator< IteratorR > &rhs)
    {
        return !(operator>(lhs, rhs));
    }

    template< class IteratorL, class IteratorR >
    typename random_access_iterator< IteratorL >::difference_type
    operator-(const random_access_iterator< IteratorL > &lhs,
              const random_access_iterator< IteratorR > &rhs)
    {
        return (lhs.base() - rhs.base());
    }

    template< class Iterator >
    random_access_iterator< Iterator >
    operator-(const int &lhs,
              const random_access_iterator< Iterator > &rhs)
    {
        return rhs - lhs;
    }


    template< class Iterator >
    typename random_access_iterator< Iterator >::difference_type
    operator+(const random_access_iterator< Iterator > &lhs,
              const random_access_iterator< Iterator > &rhs)
    {
        return (lhs.base() + rhs.base());
    }

    template< class Iterator >
    random_access_iterator< Iterator >
    operator+(const int &lhs,
              const random_access_iterator< Iterator > &rhs)
    {
        return rhs + lhs;
    }

    template< typename IteratorL, typename IteratorR >
    inline bool operator==(const random_access_iterator< IteratorL > &lhs,
                           const random_access_iterator< IteratorR > &rhs)
    {
        return lhs.base() == rhs.base();
    }


    template< typename IteratorL, typename IteratorR >
    bool operator!=(const random_access_iterator< IteratorL > &lhs,
                    const random_access_iterator< IteratorR > &rhs)
    {
        return (!(lhs.base() == rhs.base()));
    }

    template<typename Iterator>
    typename iterator_traits<Iterator>::iterator_category _iterator_category(const Iterator&)
    {
        return typename iterator_traits<Iterator>::iterator_category();
    }

    template<typename RandomAccessIterator>
    typename iterator_traits<RandomAccessIterator>::difference_type _distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag)
    {
        return last - first;
    }

    template<typename InputIterator>
    typename iterator_traits<InputIterator>::difference_type _distance(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }
} // namespace ft


#endif //FT_RANDOM_ACCESS_ITERATOR_HPP

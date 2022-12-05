//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_ITERATOR_HPP
#define FT_ITERATOR_HPP


#include <cstddef>

namespace ft {

    /* ===========================================================================================================
     * ITERATOR CATEGORIES
     * =========================================================================================================*/

    /* Empty class to identify the category of an iterator as an input iterator */
    class   input_iterator_tag {};
    /* Empty class to identify the category of an iterator as an output iterator */
    class   output_iterator_tag {};
    /* Empty class to identify the category of an iterator as a forward iterator */
    class   forward_iterator_tag {};
    /* Empty class to identify the category of an iterator as a bidirectional iterator */
    class   bidirectional_iterator_tag {};
    /* Empty class to identify the category of an iterator as a random-access iterator */
    class   random_access_iterator_tag {};


    /* ===========================================================================================================
     * ITERATOR
     * =========================================================================================================*/

    /**
     * This is a base class template that can be used to derive iterator classes from it.
     * It is not an iterator class and does not provide any of the functionality an iterator is expected to have.
     * @tparam Category Category to which the iterator belongs to. It must be one of the following iterator tags
     * @tparam T Type of elements pointed by the iterator.
     * @tparam Distance Type to represent the difference between two iterators.
     * @tparam Pointer Type to represent a pointer to an element pointed by the iterator.
     * @tparam Reference Type to represent a reference to an element pointed by the iterator.
     */
    template <class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T&>
    class iterator {
    public:
        typedef Category    iterator_category;
        typedef T           value_type;
        typedef Distance    difference_type;
        typedef Pointer     pointer;
        typedef Reference   reference;
    };


    /* ===========================================================================================================
     * ITERATOR_TRAITS
     * =========================================================================================================*/

    /**
     * Traits class defining properties of iterators.
     * Standard algorithms determine certain properties of the iterators passed to them and the range
     * they represent by using the members of the corresponding iterator_traits instantiation.
     * @tparam Iterator ft::iterator
     */
    template< class Iterator >
    class iterator_traits {
    public:
        typedef typename Iterator::difference_type      difference_type;
        typedef typename Iterator::value_type           value_type;
        typedef typename Iterator::pointer              pointer;
        typedef typename Iterator::reference            reference;
        typedef typename Iterator::iterator_category    iterator_category;
    };

    template< class T >
    class iterator_traits<T*> {
    public:
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef T*                              pointer;
        typedef T&                              reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

    template< class T >
    class iterator_traits<const T*> {
    public:
        typedef ptrdiff_t                       difference_type;
        typedef T                               value_type;
        typedef const T*                        pointer;
        typedef const T&                        reference;
        typedef ft::random_access_iterator_tag  iterator_category;
    };

    template < typename InputIterator >
    typename iterator_traits<InputIterator>::difference_type distance(InputIterator first, InputIterator last)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }
}

#endif //FT_ITERATOR_HPP

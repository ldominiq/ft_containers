//
// Created by Lucas on 29-Nov-22.
//

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include <functional>
#include "utility.hpp"
#include "reverse_iterator.hpp"

namespace ft {
    //TODO: create Nested function class to compare elements -> ft::Comp
    //TODO: create bidirectional iterator
    /**
     *Maps are associative containers that store elements formed by a combination of a key value and a mapped value,
     * following a specific order.
     * @tparam Key Type of the keys. Each element in a map is uniquely identified by its key value.
     * @tparam T Type of the mapped value. Each element in a map stores some data as its mapped value.
     * @tparam Compare A binary predicate that takes two element keys as arguments and returns a bool.
     * @tparam Alloc Type of the allocator object used to define the storage allocation model.
     */
    template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map {
    public:
        typedef Key                                             key_type;
        typedef T                                               mapped_type;
        typedef ft::pair<const key_type, mapped_type>           value_type;
        typedef Compare                                         key_compare;
        //typedef ft::Comp<>                                      value_compare;
        typedef Alloc                                           allocator_type;
        typedef typename allocator_type::reference              reference;
        typedef typename allocator_type::const_reference        const_reference;
        typedef typename allocator_type::pointer                pointer;
        typedef typename allocator_type::const_pointer          const_pointer;
        //typedef ft::map_iterator<>                              iterator;
        //typedef ft::map_iterator<>                              const_iterator;
        //typedef ft::reverse_iterator<iterator>                  reverse_iterator;
        //typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
        typedef ptrdiff_t                                       difference_type;
        typedef size_t                                          size_type;
    };
}

#endif //FT_MAP_HPP

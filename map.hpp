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

        /* ===========================================================================================================
         * PUBLIC MEMBER TYPES
         * =========================================================================================================*/

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

    private:

    public:

        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => CONSTRUCTOR / DESTRUCTOR / operator=
         * =========================================================================================================*/

        /**
         * empty container constructor (default constructor)
         * Constructs an empty container, with no elements.
         * @param comp Binary predicate that, taking two element keys as argument,
         * returns true if the first argument goes before the second argument in the strict weak ordering it defines,
         * and false otherwise.
         * This shall be a function pointer or a function object.
         * @param alloc Allocator object.
         * The container keeps and uses an internal copy of this allocator.
         */
        explicit map (const key_compare& comp = key_compare(),
                      const allocator_type& alloc = allocator_type());

        /**
         * range constructor
         * Constructs a container with as many elements as the range [first,last),
         * with each element constructed from its corresponding element in that range.
         * @tparam InputIterator
         * @param first Input iterators to the initial and final positions in a range. The range used is [first,last),
         * which includes all the elements between first and last,
         * including the element pointed by first but not the element pointed by last.
         * @param last see -> first
         * @param comp Binary predicate that, taking two element keys as argument,
         * returns true if the first argument goes before the second argument in the strict weak ordering it defines,
         * and false otherwise.
         * This shall be a function pointer or a function object.
         * @param alloc Allocator object.
         */
        template <class InputIterator>
        map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
             const allocator_type& alloc = allocator_type());

        /**
         * copy constructor
         * Constructs a container with a copy of each of the elements in x.
         * @param x Another map object of the same type (with the same class template arguments Key, T,
         * Compare and Alloc), whose contents are either copied or acquired.
         */
        map (const map& x);

        /**
         * This destroys all container elements,
         * and deallocates all the storage capacity allocated by the map container using its allocator.
         */
        ~map();

        /**
         * Copies all the elements from x into the container, changing its size accordingly.
         * @param x A map object of the same type (i.e., with the same template parameters, key, T, Compare and Alloc).
         * @return *this
         */
        map& operator= (const map& x) {

            return *this;
        }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ITERATORS
         * =========================================================================================================*/

        /**
         * Returns an iterator referring to the first element in the map container.
         * @return An iterator to the first element in the container.
         */
        iterator begin();

        /**
         * Returns an iterator referring to the first element in the map container.
         * @return A const iterator to the first element in the container.
         */
        const_iterator begin() const;

        /**
         * Returns an iterator referring to the past-the-end element in the map container.
         * @return An iterator to the past-the-end element in the container.
         */
        iterator end();

        /**
         * Returns an iterator referring to the past-the-end element in the map container.
         * @return A const iterator to the past-the-end element in the container.
         */
        const_iterator end() const;

        /**
         * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
         * @return A reverse iterator to the reverse beginning of the sequence container.
         */
        reverse_iterator rbegin();

        /**
         * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
         * @return A const reverse iterator to the reverse beginning of the sequence container.
         */
        const_reverse_iterator rbegin() const;

        /**
         * Returns a reverse iterator pointing to the theoretical element right before the first element in the
         * map container (which is considered its reverse end).
         * @return A reverse iterator to the reverse end of the sequence container.
         */
        reverse_iterator rend();

        /**
         * Returns a reverse iterator pointing to the theoretical element right before the first element in the
         * map container (which is considered its reverse end).
         * @return A const reverse iterator to the reverse end of the sequence container.
         */
        const_reverse_iterator rend() const;


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => CAPACITY
         * =========================================================================================================*/




        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ELEMENT ACCESS
         * =========================================================================================================*/




        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => MODIFIERS
         * =========================================================================================================*/




        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => OBSERVERS
         * =========================================================================================================*/




        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => OPERATIONS
         * =========================================================================================================*/




        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ALLOCATOR
         * =========================================================================================================*/


    };
}

#endif //FT_MAP_HPP

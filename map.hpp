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

        //TODO: Implement CONSTRUCTOR / DESTRUCTOR / operator=
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

        //TODO: Implement ITERATORS functions
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

        //TODO: Implement CAPACITY functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => CAPACITY
         * =========================================================================================================*/

        /**
         * Returns whether the map container is empty (i.e. whether its size is 0).
         * @return true if the container size is 0, false otherwise.
         */
        bool empty() const;

        /**
         * Returns the number of elements in the map container.
         * @return The number of elements in the container.
         */
        size_type size() const;

        /**
         * Returns the maximum number of elements that the map container can hold.
         * @return The maximum number of elements a map container can hold as content.
         */
        size_type max_size() const;

        //TODO: Implement ELEMENT ACCESS functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ELEMENT ACCESS
         * =========================================================================================================*/

        /**
         * If k matches the key of an element in the container, the function returns a reference to its mapped value.
         * @param k Key value of the element whose mapped value is accessed.
         * @return A reference to the mapped value of the element with a key value equivalent to k.
         */
        mapped_type& operator[] (const key_type& k);

        /**
         * Returns a reference to the mapped value of the element identified with key k.
         * @param k Key value of the element whose mapped value is accessed.
         * @return A reference to the mapped value of the element with a key value equivalent to k.
         */
        mapped_type& at (const key_type& k);

        /**
         * Returns a reference to the mapped value of the element identified with key k.
         * @param k Key value of the element whose mapped value is accessed.
         * @return A reference to the const mapped value of the element with a key value equivalent to k.
         */
        const mapped_type& at (const key_type& k) const;

        //TODO: Implement MODIFIERS functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => MODIFIERS
         * =========================================================================================================*/

        /**
         * Extends the container by inserting new elements,
         * effectively increasing the container size by the number of elements inserted.
         * @param val Value to be copied to (or moved as) the inserted element.
         * @return return a pair, with its member pair::first set to an iterator pointing to either the newly inserted
         * element or to the element with an equivalent key in the map. The pair::second element in the pair is set
         * to true if a new element was inserted or false if an equivalent key already existed.
         */
        pair<iterator,bool>
        insert (const value_type& val);

        /**
         * Extends the container by inserting new elements,
         * effectively increasing the container size by the number of elements inserted.
         * @param position Hint for the position where the element can be inserted.
         * @param val Value to be copied to (or moved as) the inserted element.
         * @return return an iterator pointing to either the newly inserted element or to the element that already had
         * an equivalent key in the map.
         */
        iterator insert (iterator position, const value_type& val);

        /**
         * Extends the container by inserting new elements,
         * effectively increasing the container size by the number of elements inserted.
         * @tparam InputIterator
         * @param first Iterators specifying a range of elements.
         * Copies of the elements in the range [first,last) are inserted in the container.
         * @param last see -> first
         */
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last);

        /**
         * Removes from the map container either a single element or a range of elements ([first,last)).
         * @param position Iterator pointing to a single element to be removed from the map.
         */
        void erase (iterator position);

        /**
         * Removes from the map container either a single element or a range of elements ([first,last)).
         * @param k Key of the element to be removed from the map.
         * @return the function returns the number of elements erased.
         */
        size_type erase (const key_type& k);

        /**
         * Removes from the map container either a single element or a range of elements ([first,last)).
         * @param first Iterators specifying a range within the map container to be removed: [first,last). i.e.,
         * the range includes all the elements between first and last, including the element pointed by first but not
         * the one pointed by last.
         * @param last see -> first
         */
        void erase (iterator first, iterator last);

        /**
         * Exchanges the content of the container by the content of x, which is another map of the same type.
         * Sizes may differ.
         * @param x Another map container of the same type as this (i.e., with the same template parameters, Key, T,
         * Compare and Alloc) whose content is swapped with that of this container.
         */
        void swap (map& x);

        /**
         * Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
         */
        void clear();

        //TODO: Implement OBSERVERS functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => OBSERVERS
         * =========================================================================================================*/

        /**
         * Returns a copy of the comparison object used by the container to compare keys.
         * @return The comparison object.
         */
        key_compare key_comp() const;

        /**
         * Returns a comparison object that can be used to compare two elements to get whether the key of the first
         * one goes before the second.
         * @return The comparison object for element values.
         */
        value_compare value_comp() const;


        //TODO: Implement OPERATIONS functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => OPERATIONS
         * =========================================================================================================*/

        /**
         * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
         * otherwise it returns an iterator to map::end.
         * @param k Key to be searched for.
         * @return An iterator to the element, if an element with specified key is found, or map::end otherwise.
         */
        iterator find (const key_type& k);

        /**
         * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
         * otherwise it returns an iterator to map::end.
         * @param k Key to be searched for.
         * @return A const iterator to the element, if an element with specified key is found, or map::end otherwise.
         */
        const_iterator find (const key_type& k) const;

        /**
         * Searches the container for elements with a key equivalent to k and returns the number of matches.
         * @param k Key to search for.
         * @return 1 if the container contains an element whose key is equivalent to k, or zero otherwise.
         */
        size_type count (const key_type& k) const;

        /**
         * Returns an iterator pointing to the first element in the container whose key is not
         * considered to go before k (i.e., either it is equivalent or goes after).
         * @param k Key to search for.
         * @return An iterator to the the first element in the container whose key is not considered to go before k,
         * or map::end if all keys are considered to go before k.
         */
        iterator lower_bound (const key_type& k);

        /**
         * Returns a const iterator pointing to the first element in the container whose key is not
         * considered to go before k (i.e., either it is equivalent or goes after).
         * @param k Key to search for.
         * @return A const iterator to the the first element in the container whose key is not considered to go before k,
         * or map::end if all keys are considered to go before k.
         */
        const_iterator lower_bound (const key_type& k) const;

        /**
         * Returns an iterator pointing to the first element in the container whose key is considered to go after k.
         * @param k Key to search for.
         * @return An iterator to the the first element in the container whose key is considered to go after k,
         * or map::end if no keys are considered to go after k.
         */
        iterator upper_bound (const key_type& k);

        /**
         * Returns a const iterator pointing to the first element in the container whose key is considered to go after k.
         * @param k Key to search for.
         * @return A const iterator to the the first element in the container whose key is considered to go after k,
         * or map::end if no keys are considered to go after k.
         */
        const_iterator upper_bound (const key_type& k) const;

        /**
         * Returns the bounds of a range that includes all the elements in the container which have a key
         * equivalent to k.
         * @param k Key to search for.
         * @return The function returns a pair, whose member pair::first is the lower bound of the range
         * (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
         */
        pair<const_iterator,const_iterator>
        equal_range (const key_type& k) const;

        /**
         * Returns the bounds of a range that includes all the elements in the container which have a key
         * equivalent to k.
         * @param k Key to search for.
         * @return The function returns a pair of const_iterator, whose member pair::first is the lower bound of the
         * range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
         */
        pair<iterator,iterator>
        equal_range (const key_type& k);

        //TODO: Implement ALLOCATOR function
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ALLOCATOR
         * =========================================================================================================*/

        /**
         * Returns a copy of the allocator object associated with the map.
         * @return The allocator.
         */
        allocator_type get_allocator() const;

    };
}

#endif //FT_MAP_HPP

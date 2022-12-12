//
// Created by Lucas on 29-Nov-22.
//

#ifndef FT_MAP_HPP
#define FT_MAP_HPP

#include <memory>
#include <functional>
#include "utility.hpp"
#include "bidirectional_map_iterator.hpp"
#include "type_traits.hpp"

namespace ft {

    template <class Compare, class T>
    class value_comp {
    public:

        Compare _comp;

        value_comp(Compare c) : _comp(c) {}

        /**
         * Returns a comparison object that can be used to compare two elements to get whether the key of
         * the first one goes before the second.
         * @param x
         * @param y
         * @return The comparison object for element values.
         */
        bool operator()(const T& x, const T& y) const { return _comp(x.first, y.first); }
    };

    /**
     *Maps are associative containers that store elements formed by a combination of a key value and a mapped value,
     * following a specific order.
     * @tparam Key Type of the keys. Each element in a map is uniquely identified by its key value.
     * @tparam T Type of the mapped value. Each element in a map stores some data as its mapped value.
     * @tparam Compare A binary predicate that takes two element keys as arguments and returns a bool.
     * @tparam Alloc Type of the allocator object used to define the storage allocation model.
     */
    template < class Key, class T, class Compare = std::less<Key>,
            class Alloc = std::allocator<ft::pair<const Key,T> > >
    class map {
    public:

        /* ===========================================================================================================
         * PUBLIC MEMBER TYPES
         * =========================================================================================================*/

        typedef Key                                                             key_type;
        typedef T                                                               mapped_type;
        typedef ft::pair<const key_type, mapped_type>                           value_type;
        typedef Compare                                                         key_compare;
        typedef ft::value_comp<Compare, value_type>                             value_compare;
        typedef Alloc                                                           allocator_type;
        typedef typename allocator_type::reference                              reference;
        typedef typename allocator_type::const_reference                        const_reference;
        typedef typename allocator_type::pointer                                pointer;
        typedef typename allocator_type::const_pointer                          const_pointer;
        typedef ft::bidirectional_map_iterator<key_type, mapped_type>           iterator;
        typedef ft::bidirectional_map_iterator<key_type, mapped_type, true>     const_iterator;
        typedef ft::reverse_iterator<iterator>                                  reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>                            const_reverse_iterator;
        typedef ptrdiff_t                                                       difference_type;
        typedef size_t                                                          size_type;
        typedef Node<value_type>                                                node_type;
        typedef typename Alloc::template rebind<node_type>::other               alloc_node_type;

    private:
        alloc_node_type     _alloc_node;
        allocator_type      _alloc;
        key_compare         _comp;
        size_type           _size;
        node_type           *_container;

    private:
        node_type *get_root() const { return _container->_parent; }
        node_type *get_left() const { return _container->_left; }
        node_type *get_right() const { return _container->_right; }

        void  set_left_right() {
            node_type *tmp = get_root();

            if (!tmp) {
                _container->_left = _container;
                _container->_right = _container;
                return ;
            }
            while (tmp && tmp->_left)
                tmp = tmp->_left;
            _container->_left = tmp;

            tmp = get_root();
            while (tmp && tmp->_right)
                tmp = tmp->_right;
            _container->_right = tmp;
        }

        node_type	*insert_node(node_type *node, key_compare comp, value_type pair) {
            if (node == _container) {
                if (!node->_parent) {
                    node->_parent = _alloc_node.allocate(1);
                    node->_parent->_left = NULL;
                    node->_parent->_right = NULL;
                    node->_parent->_parent = node;
                    _alloc.construct(&node->_parent->_pair, pair);

                    set_left_right();
                    return node->_parent;
                }
                else
                    node = node->_parent;
            }
            if (comp(pair.first, node->_pair.first)) {
                if (!node->_left) {
                    node->_left = _alloc_node.allocate(1);
                    node->_left->_left = NULL;
                    node->_left->_right = NULL;
                    node->_left->_parent = node;
                    _alloc.construct(&node->_left->_pair, pair);

                    set_left_right();
                    return node->_left;
                }
                else
                    node = insert_node(node->_left, comp, pair);
            }
            else {
                if (!node->_right) {
                    node->_right = _alloc_node.allocate(1);
                    node->_right->_left = NULL;
                    node->_right->_right = NULL;
                    node->_right->_parent = node;
                    _alloc.construct(&node->_right->_pair, pair);

                    set_left_right();
                    return node->_right;
                }
                else
                    node = insert_node(node->_right, comp, pair);
            }
            return node;
        }

        node_type *key_exists_recurse(node_type *node, key_type key) const {
            if (!node) {
                return NULL;
            }

            if (_comp(key, (node->_pair.first))) {
                return key_exists_recurse (node->_left, key);
            }
            else if (_comp((node->_pair.first), key)) {
                return key_exists_recurse (node->_right, key);
            }
            else {
                return node;
            }
        }

        size_type key_count_recurse(node_type *root, key_type key) const {
            if (!root)
                return 0;
            if (!_comp(root->_pair.first, key) && !_comp(key, root->_pair.first))
                return 1;
            return key_count_recurse(root->_left, key) + key_count_recurse(root->_right, key);
        }

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
                      const allocator_type& alloc = allocator_type())
                      : _alloc(alloc), _comp(comp), _size(0) {
            _container = _alloc_node.allocate(1);
            _container->_left = _container;
            _container->_right = _container;
            _container->_parent = NULL;
            _alloc.construct(&_container->_pair, value_type());
        }

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
             const allocator_type& alloc = allocator_type())
             : _alloc(alloc), _comp(comp), _size(0) {
                _container = _alloc_node.allocate(1);
                _container->_left = _container;
                _container->_right = _container;
                _container->_parent = NULL;
                this->insert(first, last);
             }

        /**
         * copy constructor
         * Constructs a container with a copy of each of the elements in x.
         * @param x Another map object of the same type (with the same class template arguments Key, T,
         * Compare and Alloc), whose contents are either copied or acquired.
         */
        map (const map& x) : _alloc(x._alloc), _comp(x._comp), _size(0) {
            _container = _alloc_node.allocate(1);
            _container->_left = _container;
            _container->_right = _container;
            _container->_parent = NULL;
            _alloc.construct(&_container->_pair, value_type());

            insert(x.begin(), x.end());
        }

        /**
         * This destroys all container elements,
         * and deallocates all the storage capacity allocated by the map container using its allocator.
         */
        ~map() {
            clear();
            _alloc.destroy(&_container->_pair);
            _alloc_node.deallocate(_container, 1);
        }

        /**
         * Copies all the elements from x into the container, changing its size accordingly.
         * @param x A map object of the same type (i.e., with the same template parameters, key, T, Compare and Alloc).
         * @return *this
         */
        map& operator= (const map& x) {
            if (this == &x)
                return *this;
            if (this->_size != 0)
                this->clear();
            this->insert(x.begin(), x.end());
            return *this;
        }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ITERATORS
         * =========================================================================================================*/

        /**
         * Returns an iterator referring to the first element in the map container.
         * @return An iterator to the first element in the container.
         */
        iterator begin() { return iterator(get_left()); }

        /**
         * Returns an iterator referring to the first element in the map container.
         * @return A const iterator to the first element in the container.
         */
        const_iterator begin() const { return const_iterator(get_left()); }

        /**
         * Returns an iterator referring to the past-the-end element in the map container.
         * @return An iterator to the past-the-end element in the container.
         */
        iterator end() { return iterator(_container); }

        /**
         * Returns an iterator referring to the past-the-end element in the map container.
         * @return A const iterator to the past-the-end element in the container.
         */
        const_iterator end() const { return (const_iterator(_container)); }

        /**
         * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
         * @return A reverse iterator to the reverse beginning of the sequence container.
         */
        reverse_iterator rbegin() { return (reverse_iterator(end())); }

        /**
         * Returns a reverse iterator pointing to the last element in the container (i.e., its reverse beginning).
         * @return A const reverse iterator to the reverse beginning of the sequence container.
         */
        const_reverse_iterator rbegin() const { return (const_reverse_iterator(end())); }

        /**
         * Returns a reverse iterator pointing to the theoretical element right before the first element in the
         * map container (which is considered its reverse end).
         * @return A reverse iterator to the reverse end of the sequence container.
         */
        reverse_iterator rend() { return (reverse_iterator(begin())); }

        /**
         * Returns a reverse iterator pointing to the theoretical element right before the first element in the
         * map container (which is considered its reverse end).
         * @return A const reverse iterator to the reverse end of the sequence container.
         */
        const_reverse_iterator rend() const { return (const_reverse_iterator(begin())); }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => CAPACITY
         * =========================================================================================================*/

        /**
         * Returns whether the map container is empty (i.e. whether its size is 0).
         * @return true if the container size is 0, false otherwise.
         */
        bool empty() const { return (begin() == end()); }

        /**
         * Returns the number of elements in the map container.
         * @return The number of elements in the container.
         */
        size_type size() const { return this->_size; }

        /**
         * Returns the maximum number of elements that the map container can hold.
         * @return The maximum number of elements a map container can hold as content.
         */
        size_type max_size() const { return _alloc_node.max_size(); }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ELEMENT ACCESS
         * =========================================================================================================*/

        /**
         * If k matches the key of an element in the container, the function returns a reference to its mapped value.
         * @param k Key value of the element whose mapped value is accessed.
         * @return A reference to the mapped value of the element with a key value equivalent to k.
         */
        mapped_type& operator[] (const key_type& k) {
            return (*((this->insert(ft::make_pair(k, mapped_type()))).first)).second;
        }


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
        insert (const value_type& val) {
            node_type *exist = key_exists_recurse(get_root(), val.first);

            if (exist)
                return ft::make_pair(iterator(exist), false);
            _size++;
            return ft::make_pair(iterator(insert_node(_container, _comp, val)), true);
        }

        /**
         * Extends the container by inserting new elements,
         * effectively increasing the container size by the number of elements inserted.
         * @param position Hint for the position where the element can be inserted.
         * @param val Value to be copied to (or moved as) the inserted element.
         * @return return an iterator pointing to either the newly inserted element or to the element that already had
         * an equivalent key in the map.
         */
        iterator insert (iterator position, const value_type& val) {
            (void)position;
            node_type *exist = key_exists_recurse(get_root(), val.first);

            if (exist)
                return iterator(exist);
            _size++;
            return iterator(insert_node(_container, _comp, val));
        }

        /**
         * Extends the container by inserting new elements,
         * effectively increasing the container size by the number of elements inserted.
         * @tparam InputIterator
         * @param first Iterators specifying a range of elements.
         * Copies of the elements in the range [first,last) are inserted in the container.
         * @param last see -> first
         */
        template <class InputIterator>
        void insert (InputIterator first, InputIterator last,
                     typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0) {
            while (first != last) {
                insert(*first);
                first++;
            }
        }

        /**
         * Removes from the map container either a single element or a range of elements ([first,last)).
         * @param position Iterator pointing to a single element to be removed from the map.
         */
        void erase (iterator position) {
            node_type *current = position._ptr;
            node_type *tmp = NULL;

            if (current->_left)
            {
                tmp = current->_left;
                while (tmp->_right)
                    tmp = tmp->_right;
                if (tmp->_parent->_right == tmp)
                {
                    if (tmp->_left)
                    {
                        tmp->_parent->_right = tmp->_left;
                        tmp->_left->_parent = tmp->_parent;
                    }
                    else
                        tmp->_parent->_right = NULL;
                }
                tmp->_right = current->_right;
                if (current->_right)
                    current->_right->_parent = tmp;
                if (current->_left != tmp)
                    tmp->_left = current->_left;
                if (current->_left)
                    current->_left->_parent = tmp;
                tmp->_parent = current->_parent;
            }
            else if (current->_right)
            {
                tmp = current->_right;
                tmp->_parent = current->_parent;
            }
            if (current->_parent->_left == current)
                current->_parent->_left = tmp;
            else
                current->_parent->_right = tmp;
            if (current == get_root())
                _container->_parent = tmp;
            _alloc.destroy(&current->_pair);
            _alloc_node.deallocate(current, 1);
            _size--;
            set_left_right();
        }

        /**
         * Removes from the map container either a single element or a range of elements ([first,last)).
         * @param k Key of the element to be removed from the map.
         * @return the function returns the number of elements erased.
         */
        size_type erase (const key_type& k) {
            iterator it = begin();
            iterator tmp;
            size_type count = 0;

            while (it != end())
            {
                if (!_comp(it->first, k) && !_comp(k, it->first))
                {
                    erase(it);
                    count++;
                    return count;
                }
                else
                    it++;
            }
            return count;
        }

        /**
         * Removes from the map container either a single element or a range of elements ([first,last)).
         * @param first Iterators specifying a range within the map container to be removed: [first,last). i.e.,
         * the range includes all the elements between first and last, including the element pointed by first but not
         * the one pointed by last.
         * @param last see -> first
         */
        void erase (iterator first, iterator last) {
            iterator tmp;

            while (first != last)
            {
                tmp = first++;
                erase(tmp);
            }
        }

        /**
         * Exchanges the content of the container by the content of x, which is another map of the same type.
         * Sizes may differ.
         * @param x Another map container of the same type as this (i.e., with the same template parameters, Key, T,
         * Compare and Alloc) whose content is swapped with that of this container.
         */
        void swap (map& x) {
            node_type *tmp;
            size_type size_tmp;

            size_tmp = _size;
            _size = x._size;
            x._size = size_tmp;

            tmp = _container;
            _container = x._container;
            x._container = tmp;
        }

        /**
         * Removes all elements from the map container (which are destroyed), leaving the container with a size of 0.
         */
        void clear() { this->erase(this->begin(), this->end()); }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => OBSERVERS
         * =========================================================================================================*/

        /**
         * Returns a copy of the comparison object used by the container to compare keys.
         * @return The comparison object.
         */
        key_compare key_comp() const { return (key_compare()); }

        /**
         * Returns a comparison object that can be used to compare two elements to get whether the key of the first
         * one goes before the second.
         * @return The comparison object for element values.
         */
        value_compare value_comp() const { return (value_compare(key_compare())); }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => OPERATIONS
         * =========================================================================================================*/

        /**
         * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
         * otherwise it returns an iterator to map::end.
         * @param k Key to be searched for.
         * @return An iterator to the element, if an element with specified key is found, or map::end otherwise.
         */
        iterator find (const key_type& k) {
            node_type *found = key_exists_recurse(get_root(), k);

            if (found)
                return iterator(found);
            return (end());
        }

        /**
         * Searches the container for an element with a key equivalent to k and returns an iterator to it if found,
         * otherwise it returns an iterator to map::end.
         * @param k Key to be searched for.
         * @return A const iterator to the element, if an element with specified key is found, or map::end otherwise.
         */
        const_iterator find (const key_type& k) const {
            node_type *found = key_exists_recurse(get_root(), k);

            if (found)
                return const_iterator(found);
            return (end());
        }

        /**
         * Searches the container for elements with a key equivalent to k and returns the number of matches.
         * @param k Key to search for.
         * @return 1 if the container contains an element whose key is equivalent to k, or zero otherwise.
         */
        size_type count (const key_type& k) const { return key_count_recurse(get_root(), k); }

        /**
         * Returns an iterator pointing to the first element in the container whose key is not
         * considered to go before k (i.e., either it is equivalent or goes after).
         * @param k Key to search for.
         * @return An iterator to the the first element in the container whose key is not considered to go before k,
         * or map::end if all keys are considered to go before k.
         */
        iterator lower_bound (const key_type& k) {
            iterator it;
            for (it = this->begin(); it != this->end(); ++it)
                if (key_compare()(it->first, k) == false)
                    return (it);
            return (it);
        }

        /**
         * Returns a const iterator pointing to the first element in the container whose key is not
         * considered to go before k (i.e., either it is equivalent or goes after).
         * @param k Key to search for.
         * @return A const iterator to the the first element in the container whose key is not considered to go before
         * k, or map::end if all keys are considered to go before k.
         */
        const_iterator lower_bound (const key_type& k) const {
            const_iterator it;
            for (it = this->begin(); it != this->end(); ++it)
                if (key_compare()(it->first, k) == false)
                    return (it);
            return (it);
        }

        /**
         * Returns an iterator pointing to the first element in the container whose key is considered to go after k.
         * @param k Key to search for.
         * @return An iterator to the the first element in the container whose key is considered to go after k,
         * or map::end if no keys are considered to go after k.
         */
        iterator upper_bound (const key_type& k) {
            iterator it;
            for (it = this->begin(); it != this->end(); ++it)
                if (key_compare()(k, it->first) == true)
                    return (it);
            return (it);
        }

        /**
         * Returns a const iterator pointing to the first element in the container whose key
         * is considered to go after k.
         * @param k Key to search for.
         * @return A const iterator to the the first element in the container whose key is considered to go after k,
         * or map::end if no keys are considered to go after k.
         */
        const_iterator upper_bound (const key_type& k) const {
            const_iterator it;
            for (it = this->begin(); it != this->end(); ++it)
                if (key_compare()(k, it->first) == true)
                    return (it);
            return (it);
        }

        /**
         * Returns the bounds of a range that includes all the elements in the container which have a key
         * equivalent to k.
         * @param k Key to search for.
         * @return The function returns a pair of const_iterator, whose member pair::first is the lower bound of the
         * range (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
         */
        ft::pair<iterator,iterator>
        equal_range (const key_type& k) {
            return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
        }

        /**
         * Returns the bounds of a range that includes all the elements in the container which have a key
         * equivalent to k.
         * @param k Key to search for.
         * @return The function returns a pair, whose member pair::first is the lower bound of the range
         * (the same as lower_bound), and pair::second is the upper bound (the same as upper_bound).
         */
        ft::pair<const_iterator,const_iterator>
        equal_range (const key_type& k) const {
            return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
        }


        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ALLOCATOR
         * =========================================================================================================*/

        /**
         * Returns a copy of the allocator object associated with the map.
         * @return The allocator.
         */
        allocator_type get_allocator() const { return _alloc; }

    };

    template <class Key, class T>
    bool operator==(const map<Key, T>& lhs, const map<Key, T>& rhs)
    {
        if (lhs.size() != rhs.size())
            return false;
        typename map<Key, T>::const_iterator it1 = lhs.begin();
        typename map<Key, T>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end()) {
            if (*it1 != *it2)
                return false;
            it1++;
            it2++;
        }
        return (it1 == lhs.end()) && (it2 == rhs.end());
    }

    template <class Key, class T>
    bool operator!=(const map<Key, T>& lhs, const map<Key, T>& rhs) { return !(lhs == rhs); };

    template <class Key, class T>
    bool operator<(const map<Key, T>& lhs, const map<Key, T>& rhs)
    {
        typename map<Key, T>::const_iterator it1 = lhs.begin();
        typename map<Key, T>::const_iterator it2 = rhs.begin();

        while (it1 != lhs.end() && it2 != rhs.end()) {
            if (*it1 < *it2)
                return true;
            if (*it2 < *it1)
                return false;
            it1++;
            it2++;
        }
        return (it1 == lhs.end()) && (it2 != rhs.end());
    }

    template <class Key, class T>
    bool operator<=(const map<Key, T>& lhs, const map<Key, T>& rhs) { return !(rhs < lhs); };

    template <class Key, class T>
    bool operator>(const map<Key, T>& lhs, const map<Key, T>& rhs) { return rhs < lhs; };

    template <class Key, class T>
    bool operator>=(const map<Key, T>& lhs, const map<Key, T>& rhs) { return !(lhs < rhs); };

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc>& x, map<Key, T, Compare, Alloc>& y) {
        x.swap(y);
    }

}

#endif //FT_MAP_HPP

//
// Created by Lucas on 29-Nov-22.
//

#ifndef FT_VECTOR_HPP
#define FT_VECTOR_HPP

#include <memory>
#include "random_access_iterator.hpp"
#include "iterator.hpp"
#include "reverse_iterator.hpp"
#include "utils.hpp"

namespace ft {

    /**
     * Vectors are sequence containers representing arrays that can change in size
     * @tparam T Type of the elements.
     * @tparam Alloc Type of the allocator object used to define the storage allocation model.
     * By default, the allocator class template is used,
     * which defines the simplest memory allocation model and is value-independent.
     */
    template < class T, class Alloc = std::allocator<T> >
    class vector {
    public:

        /* ===========================================================================================================
         * PUBLIC MEMBER TYPES
         * =========================================================================================================*/

        /*  The first template parameter (T)    */
        typedef T                                               value_type;
        /*  The second template parameter (Alloc), `defaults to: allocator<value_type>` */
        typedef Alloc                                           allocator_type;
        /*  allocator_type::reference, defaults to `value_type&`    */
        typedef typename allocator_type::reference              reference;
        /*  allocator_type::const_reference, defaults to `const value_type&`    */
        typedef typename allocator_type::const_reference        const_reference;
        /*  allocator_type::pointer, defaults to `value_type*` */
        typedef typename allocator_type::pointer                pointer;
        /*  allocator_type::const_pointer, defaults to `const value_type*` */
        typedef typename allocator_type::const_pointer          const_pointer;

        /*  a random access iterator to value_type */
        typedef ft::random_access_iterator<value_type>          iterator;

        /*  a random access iterator to const value_type */
        typedef ft::random_access_iterator<const value_type>    const_iterator;

        /* 	reverse_iterator<iterator>  */
        typedef ft::reverse_iterator<iterator>                  reverse_iterator;

        /*  reverse_iterator<const_iterator>    */
        typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;

        /*  a signed integral type, identical to:    iterator_traits<iterator>::difference_type */
        typedef typename allocator_type::difference_type        difference_type;

        /*  an unsigned integral type that can represent any non-negative value of difference_type  */
        typedef typename allocator_type::size_type              size_type;

    private:
        allocator_type  _alloc;
        pointer         _start;
        pointer         _end;
        pointer         _end_capacity;

    public:

        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => CONSTRUCTOR / DESTRUCTOR / operator=
         * =========================================================================================================*/

        /**
         * empty container constructor (default constructor)
         * Constructs an empty container, with no elements.
         * @param alloc Allocator object.
         */
        explicit vector (const allocator_type& alloc = allocator_type())
            : _alloc(alloc), _start(0), _end(0), _end_capacity(0) {};

        /**
         * fill constructor
         * Constructs a container with n elements. Each element is a copy of val.
         * @param n Initial container size (i.e., the number of elements in the container at construction).
         * @param val Value to fill the container with. Each of the n elements in the container will be initialized to
         * a copy of this value.
         * Member type value_type is the type of the elements in the container,
         * defined in vector as an alias of its first template parameter (T).
         * @param alloc Allocator object.
         */
        explicit vector (size_type n, const value_type& val = value_type(),
                         const allocator_type& alloc = allocator_type())
                         : _alloc(alloc) {
            this->_start = this->_alloc.allocate(n);
            this->_end = this->_start;
            this->_end_capacity = this->_start + n;
            while (n--) this->_alloc.construct(this->_end++, val);
        }

        /**
         * range constructor
         * Constructs a container with as many elements as the range [first,last),
         * with each element constructed from its corresponding element in that range, in the same order.
         * @tparam InputIterator
         * @param first -> see last
         * @param last Input iterators to the initial and final positions in a range.
         * The range used is [first,last), which includes all the elements between first and last,
         * including the element pointed by first but not the element pointed by last.
         * The function template argument InputIterator shall be an input iterator type that points to elements of
         * a type from which value_type objects can be constructed.
         * @param alloc Allocator object.
         */
        template <class InputIterator>
        vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
            : _alloc(alloc) {
            size_type n = ft::distance(first, last);
            this->_start = this->_alloc.allocate(n);
            this->_end_capacity = this->_start + n;
            this->_end = this->_start;
            while (n--) this->_alloc.construct(this->_end++, *first++);
        }

        /**
         * copy constructor
         * Constructs a container with a copy of each of the elements in x, in the same order.
         * @param x Another vector object of the same type (with the same class template arguments T and Alloc),
         * whose contents are either copied or acquired.
         */
        vector (const vector& x) : _alloc(x._alloc){
            size_type n = x.size();
            this->_start = this->_alloc.allocate(n);
            this->_end_capacity = this->_start + n;
            this->_end = this->_start;

            pointer other = x._start;
            while (n--) this->_alloc.construct(this->_end++, *other++);
        }

        /**
         * This destroys all container elements, and deallocates all the storage capacity allocated
         * by the vector using its allocator.
         */
        ~vector() {
            this->clear();
            this->_alloc.deallocate(this->_start, this->capacity());
        }

        /**
         * Copies all the elements from x into the container.
         * @param x A vector object of the same type (i.e., with the same template parameters, T and Alloc).
         * @return *this
         */
        vector& operator= (const vector& x) {
            if (this != &x) {
                this->clear();
                this->insert(this->_start, x.begin(), x.end());
            }
            return *this;
        }


        //TODO: implement iterator functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ITERATORS
         * =========================================================================================================*/

        /**
         * Returns an iterator pointing to the first element in the vector.
         * Notice that, unlike member vector::front, which returns a reference to the first element,
         * this function returns a random access iterator pointing to it.
         * @return An iterator to the beginning of the sequence container.
         */
        iterator begin();

        /**
         * Returns an iterator pointing to the first element in the vector.
         * @return An iterator to the beginning of the sequence container.
         */
        const_iterator begin() const;

        /**
         * Returns an iterator referring to the past-the-end element in the vector container.
         * The past-the-end element is the theoretical element that would follow the last element in the vector.
         * It does not point to any element, and thus shall not be dereferenced.
         * @return An iterator to the element past the end of the sequence.
         */
        iterator end();

        /**
         * Returns an iterator referring to the past-the-end element in the vector container.
         * @return An iterator to the element past the end of the sequence.
         */
        const_iterator end() const;

        /**
         * Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
         * Reverse iterators iterate backwards: increasing them moves them towards the beginning of the container.
         * rbegin points to the element right before the one that would be pointed to by member end.
         * @return A reverse iterator to the reverse beginning of the sequence container.
         */
        reverse_iterator rbegin();

        /**
         * Returns a reverse iterator pointing to the last element in the vector (i.e., its reverse beginning).
         * @return A reverse iterator to the reverse beginning of the sequence container.
         */
        const_reverse_iterator rbegin() const;

        /**
         * Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
         * (which is considered its reverse end).
         * @return A reverse iterator to the reverse end of the sequence container.
         */
        reverse_iterator rend();

        /**
         * Returns a reverse iterator pointing to the theoretical element preceding the first element in the vector
         * (which is considered its reverse end).
         * @return A reverse iterator to the reverse end of the sequence container.
         */
        const_reverse_iterator rend() const;


        //TODO: implement capacity functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => CAPACITY
         * =========================================================================================================*/

        /**
         * Returns the number of elements in the vector.
         * This is the number of actual objects held in the vector,
         * which is not necessarily equal to its storage capacity.
         * @return The number of elements in the container.
         */
        size_type size() const;

        /**
         * Returns the maximum number of elements that the vector can hold.
         * @return The maximum number of elements a vector container can hold as content.
         */
        size_type max_size() const;

        /**
         * Resizes the container so that it contains n elements.
         * @param n New container size, expressed in number of elements.
         * @param val Object whose content is copied to the added elements in case that n is greater than the current
         * container size. If not specified, the default constructor is used instead.
         * Member type value_type is the type of the elements in the container,
         * defined in vector as an alias of the first template parameter (T).
         */
        void resize (size_type n, value_type val = value_type());

        /**
         * Returns the size of the storage space currently allocated for the vector, expressed in terms of elements.
         * @return The size of the currently allocated storage capacity in the vector,
         * measured in terms of the number elements it can hold.
         */
        size_type capacity() const;

        /**
         * Returns whether the vector is empty (i.e. whether its size is 0).
         * @return true if the container size is 0, false otherwise.
         */
        bool empty() const;

        /**
         * Requests that the vector capacity be at least enough to contain n elements.
         * @param n Minimum capacity for the vector.
         * Note that the resulting vector capacity may be equal or greater than n.
         */
        void reserve (size_type n);


        //TODO: implement element access functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ELEMENT ACCESS
         * =========================================================================================================*/

        /**
         * Returns a reference to the element at position n in the vector container.
         * A similar member function, vector::at, has the same behavior as this operator function,
         * except that vector::at is bound-checked and signals if the requested position is out of range
         * by throwing an out_of_range exception.
         * @param n Position of an element in the container.
         * @return The element at the specified position in the vector.
         */
        reference operator[] (size_type n);

        /**
         * Returns a reference to the element at position n in the vector container.
         * @param n Position of an element in the container.
         * @return The element at the specified position in the vector.
         */
        const_reference operator[] (size_type n) const;

        /**
         * Returns a reference to the element at position n in the vector.
         * The function automatically checks whether n is within the bounds of valid elements in the vector,
         * throwing an out_of_range exception if it is not (i.e., if n is greater than, or equal to, its size).
         * This is in contrast with member operator[], that does not check against bounds.
         * @param n Position of an element in the container.
         * @return The element at the specified position in the container.
         */
        reference at (size_type n);

        /**
         * Returns a reference to the element at position n in the vector.
         * @param n Position of an element in the container.
         * @return The element at the specified position in the container.
         */
        const_reference at (size_type n) const;

        /**
         * Returns a reference to the first element in the vector.
         * Unlike member vector::begin, which returns an iterator to this same element,
         * this function returns a direct reference.
         * @return A reference to the first element in the vector container.
         */
        reference front();

        /**
         * Returns a reference to the first element in the vector.
         * @return A reference to the first element in the vector container.
         */
        const_reference front() const;

        /**
         * Returns a reference to the last element in the vector.
         * Unlike member vector::end, which returns an iterator just past this element,
         * this function returns a direct reference.
         * @return A reference to the last element in the vector.
         */
        reference back();

        /**
         * Returns a reference to the last element in the vector.
         * @return A reference to the last element in the vector.
         */
        const_reference back() const;


        //TODO: implement modifiers functions
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => MODIFIERS
         * =========================================================================================================*/

        /**
         * Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
         * the new contents are elements constructed from each of the elements in the range between first and last,
         * in the same order.
         * @tparam InputIterator
         * @param first Input iterators to the initial and final positions in a sequence.
         * The range used is [first,last), which includes all the elements between first and last,
         * including the element pointed by first but not the element pointed by last.
         * @param last see -> first
         */
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last);

        /**
         * Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
         * the new contents are n elements, each initialized to a copy of val.
         * @param n New size for the container.
         * @param val Value to fill the container with.
         * Each of the n elements in the container will be initialized to a copy of this value.
         */
        void assign (size_type n, const value_type& val);

        /**
         * Adds a new element at the end of the vector, after its current last element.
         * The content of val is copied (or moved) to the new element.
         * This effectively increases the container size by one,
         * which causes an automatic reallocation of the allocated storage space if
         * -and only if- the new vector size surpasses the current vector capacity.
         * @param val Value to be copied (or moved) to the new element.
         */
        void push_back (const value_type& val);

        /**
         * Removes the last element in the vector, effectively reducing the container size by one.
         */
        void pop_back();

        /**
         * The vector is extended by inserting new elements before the element at the specified position,
         * effectively increasing the container size by the number of elements inserted.
         * @param position Position in the vector where the new elements are inserted.
         * @param val Value to be copied (or moved) to the inserted elements.
         * @return An iterator that points to the first of the newly inserted elements.
         */
        iterator insert (iterator position, const value_type& val);

        /**
         * The vector is extended by inserting new elements before the element at the specified position,
         * effectively increasing the container size by the number of elements inserted.
         * @param position Position in the vector where the new elements are inserted.
         * @param n Number of elements to insert. Each element is initialized to a copy of val.
         * @param val Value to be copied (or moved) to the inserted elements.
         */
        void insert (iterator position, size_type n, const value_type& val);

        /**
         * The vector is extended by inserting new elements before the element at the specified position,
         * effectively increasing the container size by the number of elements inserted.
         * @tparam InputIterator
         * @param position Position in the vector where the new elements are inserted.
         * @param first Iterators specifying a range of elements.
         * Copies of the elements in the range [first,last) are inserted at position (in the same order).
         * @param last see -> first
         */
        template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last);

        /**
         * Removes from the vector either a single element (position) or a range of elements ([first,last)).
         * @param position Iterator pointing to a single element to be removed from the vector.
         * @return An iterator pointing to the new location of the element that followed the last element erased by
         * the function call. This is the container end if the operation erased the last element in the sequence.
         */
        iterator erase (iterator position);

        /**
         * Removes from the vector either a single element (position) or a range of elements ([first,last)).
         * @param first Iterators specifying a range within the vector] to be removed: [first,last).
         * i.e., the range includes all the elements between first and last,
         * including the element pointed by first but not the one pointed by last.
         * @param last see -> first
         * @return An iterator pointing to the new location of the element that followed the last element erased by
         * the function call. This is the container end if the operation erased the last element in the sequence.
         */
        iterator erase (iterator first, iterator last);

        /**
         * Exchanges the content of the container by the content of x, which is another vector object of the same type.
         * Sizes may differ.
         * @param x Another vector container of the same type
         * (i.e., instantiated with the same template parameters, T and Alloc)
         * whose content is swapped with that of this container.
         */
        void swap (vector& x);

        /**
         * Removes all elements from the vector (which are destroyed), leaving the container with a size of 0.
         */
        void clear();


        //TODO: implement allocator function
        /* ===========================================================================================================
         * PUBLIC MEMBER FUNCTIONS => ALLOCATOR
         * =========================================================================================================*/

        /**
         * Returns a copy of the allocator object associated with the vector.
         * @return The allocator.
         */
        allocator_type get_allocator() const;


        //TODO: implement overloads functions
        /* ===========================================================================================================
         * NON MEMBER FUNCTION OVERLOADS
         * =========================================================================================================*/

        /**
         * Performs the appropriate comparison operation between the vector containers lhs and rhs.
         * @tparam T
         * @tparam Alloc
         * @param lhs vector containers (to the left- and right-hand side of the operator, respectively),
         * having both the same template parameters (T and Alloc).
         * @param rhs see -> lhs
         * @return true if the condition holds, and false otherwise.
         */
        template < T, Alloc>
        bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        /**
         * Performs the appropriate comparison operation between the vector containers lhs and rhs.
         * @tparam T
         * @tparam Alloc
         * @param lhs vector containers (to the left- and right-hand side of the operator, respectively),
         * having both the same template parameters (T and Alloc).
         * @param rhs see -> lhs
         * @return true if the condition holds, and false otherwise.
         */
        template < T, Alloc>
        bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        /**
         * Performs the appropriate comparison operation between the vector containers lhs and rhs.
         * @tparam T
         * @tparam Alloc
         * @param lhs vector containers (to the left- and right-hand side of the operator, respectively),
         * having both the same template parameters (T and Alloc).
         * @param rhs see -> lhs
         * @return true if the condition holds, and false otherwise.
         */
        template < T, Alloc>
        bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        /**
         * Performs the appropriate comparison operation between the vector containers lhs and rhs.
         * @tparam T
         * @tparam Alloc
         * @param lhs vector containers (to the left- and right-hand side of the operator, respectively),
         * having both the same template parameters (T and Alloc).
         * @param rhs see -> lhs
         * @return true if the condition holds, and false otherwise.
         */
        template < T, Alloc>
        bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        /**
         * Performs the appropriate comparison operation between the vector containers lhs and rhs.
         * @tparam T
         * @tparam Alloc
         * @param lhs vector containers (to the left- and right-hand side of the operator, respectively),
         * having both the same template parameters (T and Alloc).
         * @param rhs see -> lhs
         * @return true if the condition holds, and false otherwise.
         */
        template < T, Alloc>
        bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        /**
         * Performs the appropriate comparison operation between the vector containers lhs and rhs.
         * @tparam T
         * @tparam Alloc
         * @param lhs vector containers (to the left- and right-hand side of the operator, respectively),
         * having both the same template parameters (T and Alloc).
         * @param rhs see -> lhs
         * @return true if the condition holds, and false otherwise.
         */
        template < T, Alloc>
        bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs);

        /**
         * The contents of container x are exchanged with those of y.
         * Both container objects must be of the same type (same template parameters), although sizes may differ.
         * @tparam T
         * @tparam Alloc
         * @param x vector containers of the same type (i.e., having both the same template parameters, T and Alloc).
         * @param y see -> x
         */
        template < T, Alloc>
        void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);

    }; // class vector
} //namespace ft
#endif //FT_VECTOR_HPP

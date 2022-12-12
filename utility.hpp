//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft {

    /* ===========================================================================================================
     * Pair
     * =========================================================================================================*/

    /**
     * This class couples together a pair of values, which may be of different types (T1 and T2).
     * The individual values can be accessed through its public members first and second.
     * @tparam T1 Type of member first, aliased as first_type.
     * @tparam T2 Type of member second, aliased as second_type.
     */
    template <class T1, class T2>
    struct pair {
    private:
        typedef T1 first_type;
        typedef T2 second_type;

    public:
        first_type 	first;
        second_type second;

        pair() : first(), second() {};

        pair(const first_type& a, const second_type& b) : first(a), second(b) {}

        pair(const pair& rhs) : first(rhs.first), second(rhs.second){}

        template<class U, class V>
        pair(const pair<U,V>& pr) : first(pr.first), second(pr.second) {}

        operator pair<const T1, T2>() const {
            return (pair<const T1, T2>(this->first, this->second));
        }

        template<class U, class V>
        explicit pair(const pair<const U, V>& pr) : first(pr.first), second(pr.second) {}

        pair &operator=(const pair &rhs) {
            if (this != &rhs) {
                this->first = rhs.first;
                this->second = rhs.second;
            }
            return *this;
        };

        ~pair() {};

    };


    /* ===========================================================================================================
     * Relational operators for pair
     * =========================================================================================================*/

    template <class T1, class T2>
    bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template <class T1, class T2>
    bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs == rhs);
    }

    template <class T1, class T2>
    bool operator< (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(rhs < lhs);
    }

    template <class T1, class T2>
    bool operator> (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return rhs < lhs;
    }

    template <class T1, class T2>
    bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
    {
        return !(lhs < rhs);
    }


    /* ===========================================================================================================
     * Swap
     * =========================================================================================================*/

    template< class T1, class T2 >
    void swap( pair<T1,T2>& lhs, pair<T1,T2>& rhs )
    {
        lhs.swap(rhs);
    }


    /* ===========================================================================================================
     * Make pair
     * =========================================================================================================*/

    /**
     * Constructs a pair object with its first element set to x and its second element set to y.
     * @tparam T1
     * @tparam T2
     * @param x Values for the members first and second, respectively, of the pair object being constructed.
     * @param y see -> x
     * @return A pair object whose elements first and second are set to x and y respectivelly.
     */
    template <class T1, class T2>
    pair<T1,T2>
    make_pair (T1 x, T2 y) {
        return (pair<T1, T2>(x, y));
    }
}

#endif //FT_UTILITY_HPP

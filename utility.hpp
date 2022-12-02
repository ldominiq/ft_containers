//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_UTILITY_HPP
#define FT_UTILITY_HPP

namespace ft {

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

        friend bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return lhs.first==rhs.first && lhs.second==rhs.second; }

        friend bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return lhs != rhs; }

        friend bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return lhs.first < rhs.first || (rhs.first >= lhs.first && lhs.second < rhs.second); }

        friend bool operator<= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return rhs >= lhs; }

        friend bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return rhs<lhs; }

        friend bool operator>= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
        { return lhs >= rhs; }

        pair &operator=(const pair &rhs) {
            if (this != &rhs) {
                this->first = rhs.first;
                this->second = rhs.second;
            }
            return *this;
        };
        ~pair() {};
    };

    template <class T1, class T2>
    pair<T1,T2> make_pair (T1 x, T2 y) {
        return (pair<T1, T2>(x, y));
    }
}

#endif //FT_UTILITY_HPP

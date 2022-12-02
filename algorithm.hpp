//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_ALGORITHM_HPP
#define FT_ALGORITHM_HPP

namespace ft {

    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
        for (; first1 != last1; ++first1, ++first2) {
            if (*first1 != *first2) {
                return false;
            }
        }
        return true;
    }
}

#endif //FT_ALGORITHM_HPP

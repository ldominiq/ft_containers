//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP

#include "iterator.hpp"

namespace ft {
    template<typename It>
    typename ft::iterator_traits<It>::difference_type   distance(It first, It last)
    {
        typename ft::iterator_traits<It>::difference_type   rtn = 0;
        while (first != last)
        {
            ++first;
            ++rtn;
        }
        return rtn;
    }
}

#endif //FT_UTILS_HPP

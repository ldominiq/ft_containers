//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

//TODO: Implement enable_if
//TODO: Implement is_integral
namespace ft {

    template <bool Cond, class T = void>
    struct enable_if;

    template <class T>
    struct is_integral;
}

#endif //FT_TYPE_TRAITS_HPP

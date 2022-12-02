//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

namespace ft {

    /* ===========================================================================================================
     * ENABLE_IF
     * =========================================================================================================*/

    template <bool Cond, class T = void>
    struct enable_if {};

    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };


    /* ===========================================================================================================
     * IS_INTEGRAL
     * =========================================================================================================*/

    template<class T>
    class is_integral {
    public:
        static const bool value = false;
    };

    template<>
    class is_integral<int> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<bool> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<char> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<wchar_t> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<signed char> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<short int> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<long int> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<unsigned char> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<unsigned short int> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<unsigned int> {
    public:
        static const bool value = true;
    };

    template<>
    class is_integral<unsigned long int> {
    public:
        static const bool value = true;
    };
}

#endif //FT_TYPE_TRAITS_HPP

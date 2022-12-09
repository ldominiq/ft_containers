//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_TYPE_TRAITS_HPP
#define FT_TYPE_TRAITS_HPP

namespace ft {

    /* ===========================================================================================================
     * ENABLE_IF
     * =========================================================================================================*/

    /**
     * The type T is enabled as member type enable_if::type if Cond is true.
     * @tparam Cond A compile-time constant of type bool.
     * @tparam T A type.
     */
    template <bool Cond, class T = void>
    struct enable_if {};

    /**
     * The type T is enabled as member type enable_if::type if Cond is true.
     * @tparam T A type.
     */
    template<class T>
    struct enable_if<true, T> {
        typedef T type;
    };


    /* ===========================================================================================================
     * IS_INTEGRAL
     * =========================================================================================================*/

    /**
     * Trait class that identifies whether T is an integral type.
     * @tparam T A type.
     */
    template<class T>
    class is_integral {
    public:
        static const bool value = false;
    };

    /**
     * Trait class that identifies whether int is an integral type.
     */
    template<>
    class is_integral<int> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether bool is an integral type.
     */
    template<>
    class is_integral<bool> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether char is an integral type.
     */
    template<>
    class is_integral<char> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether wchar_t is an integral type.
     */
    template<>
    class is_integral<wchar_t> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether signed char is an integral type.
     */
    template<>
    class is_integral<signed char> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether short int is an integral type.
     */
    template<>
    class is_integral<short int> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether long int is an integral type.
     */
    template<>
    class is_integral<long int> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether unsigned char is an integral type.
     */
    template<>
    class is_integral<unsigned char> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether unsigned short int is an integral type.
     */
    template<>
    class is_integral<unsigned short int> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether unsigned int is an integral type.
     */
    template<>
    class is_integral<unsigned int> {
    public:
        static const bool value = true;
    };

    /**
     * Trait class that identifies whether unsigned long int is an integral type.
     */
    template<>
    class is_integral<unsigned long int> {
    public:
        static const bool value = true;
    };
}

#endif //FT_TYPE_TRAITS_HPP

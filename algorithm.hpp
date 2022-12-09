//
// Created by Lucas on 01-Dec-22.
//

#ifndef FT_ALGORITHM_HPP
#define FT_ALGORITHM_HPP

namespace ft {

    /* ===========================================================================================================
     * Equal
     * =========================================================================================================*/

    /**
     * Compares the elements in the range [first1,last1) with those in the range beginning at first2,
     * and returns true if all of the elements in both ranges match.
     * @tparam InputIterator1
     * @tparam InputIterator2
     * @param first1 Input iterators to the initial and final positions of the first sequence.
     * @param last1 Input iterators to the initial and final positions of the first sequence.
     * @param first2 Input iterator to the initial position of the second sequence.
     * @return true if all the elements in the range [first1,last1)
     * compare equal to those of the range starting at first2, and false otherwise.
     */
    template <class InputIterator1, class InputIterator2>
    bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2) {
        for (; first1 != last1; ++first1, ++first2) {
            if (*first1 != *first2) {
                return false;
            }
        }
        return true;
    }

    /**
    * Compares the elements in the range [first1,last1) with those in the range beginning at first2,
    * and returns true if all of the elements in both ranges match.
    * @tparam InputIt1
    * @tparam BinaryPredicate
    * @tparam InputIterator2
    * @param first1 Input iterators to the initial and final positions of the first sequence.
    * @param last1 Input iterators to the initial and final positions of the first sequence.
    * @param first2 Input iterator to the initial position of the second sequence.
    * @param p Binary function that accepts two elements as argument (one of each of the two sequences,
     * in the same order), and returns a value convertible to bool.
    * @return true if all the elements in the range [first1,last1)
    * compare equal to those of the range starting at first2, and false otherwise.
    */
    template<class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
        for (; first1 != last1; ++first1, ++first2) {
            if (!p(*first1, *first2)) {
                return false;
            }
        }
        return true;
    }


    /* ===========================================================================================================
     * lexicographical_compare
     * =========================================================================================================*/

    /**
     * Returns true if the range [first1,last1) compares lexicographically less than the range [first2,last2).
     * @tparam InputIt1
     * @tparam InputIt2
     * @param first1 Input iterators to the initial and final positions of the first sequence.
     * @param last1 Input iterators to the initial and final positions of the first sequence.
     * @param first2 Input iterators to the initial and final positions of the second sequence.
     * @param last2 Input iterators to the initial and final positions of the second sequence.
     * @return true if the first range compares lexicographically less than the second.
     */
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

    /**
     *
     * @tparam InputIt1
     * @tparam InputIt2
     * @tparam Compare
     * @param first1 Input iterators to the initial and final positions of the first sequence.
     * @param last1 Input iterators to the initial and final positions of the first sequence.
     * @param first2 Input iterators to the initial and final positions of the second sequence.
     * @param last2 Input iterators to the initial and final positions of the second sequence.
     * @param comp Binary function that accepts two arguments of the types pointed by the iterators,
     * and returns a value convertible to bool.
     * @return true if the first range compares lexicographically less than the second.
     */
    template<class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp) {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2)
        {
            if (comp(*first1, *first2))
                return true;
            if (comp(*first2, *first1))
                return false;
        }

        return (first1 == last1) && (first2 != last2);
    }

    template< class T >
    void swap( T& a, T& b )
    {
        T tmp;
        tmp = a;
        a = b;
        b = tmp;
    }
}

#endif //FT_ALGORITHM_HPP

#pragma once

#include <bitset>
#include <iterator>
#include <cassert>


namespace euler::itertools {

/**
 * Return the set of all subset of the given range of elements.
 *
 * The function will treat all elements in the range as different,
 * i.e. no checking for duplicates is performed.
 *
 * Note that the size of the powerset is 2^n for n elements in the
 * input set. A hard limit of n < 64 is enforced, but memory is likely
 * to be an issue before this.
 *
 * @param begin Iterator pointing to first element in the range
 * @param end Iterator pointing one past the last element in the range.
 * @return A vector of vectors of the underlying type, giving all possible subsets.
 */
template<typename Iterator, class Object = typename std::iterator_traits<Iterator>::value_type>
std::vector<std::vector<Object>> powerset(Iterator begin, Iterator end) {

    unsigned size = std::distance(begin, end);
    assert(size < 64);  // Cannot make powersets of size >= 2^64
    uint64_t power_size = 1ULL << size;

    std::vector<std::vector<Object>> pset;
    for (unsigned counter = 0; counter < power_size; ++counter) {
        std::bitset<64> bits{counter};
        std::vector<Object> set;
        for (unsigned i = 0; i < size; ++i) {
            if (bits[i]) {
                set.push_back(*(begin + i));
            }
        }
        pset.push_back(set);
    }

    // Sort the sets by increasing size.
    std::sort(pset.begin(), pset.end(),
        [](const std::vector<Object>& a, const std::vector<Object>& b) {
            return a.size() < b.size();});

    return pset;

}

}

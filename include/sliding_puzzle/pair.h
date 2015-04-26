#ifndef INCLUDE_SLIDING_PUZZLE_PAIR_H_
#define INCLUDE_SLIDING_PUZZLE_PAIR_H_

#include <algorithm>
#include <utility>
#include <vector>

namespace sliding_puzzle {

namespace pair {

template<typename First, typename Second>
inline std::vector<First> first(const std::vector<std::pair<First, Second>>&
                                pairs) {
    std::vector<First> elements(pairs.size());
    std::transform(pairs.begin(), pairs.end(), elements.begin(),
        [](const std::pair<First, Second>& pair) {
            return pair.first;
        });
    return elements;
}

template<typename First, typename Second>
inline std::vector<First> second(const std::vector<std::pair<First, Second>>&
                                 pairs) {
    std::vector<First> elements(pairs.size());
    std::transform(pairs.begin(), pairs.end(), elements.begin(),
        [](const std::pair<First, Second>& pair) {
            return pair.second;
        });
    return elements;
}

}  // namespace pair
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_PAIR_H_

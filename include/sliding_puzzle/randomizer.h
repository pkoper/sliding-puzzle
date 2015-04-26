#ifndef INCLUDE_SLIDING_PUZZLE_RANDOMIZER_H_
#define INCLUDE_SLIDING_PUZZLE_RANDOMIZER_H_

#include <vector>

#include "sliding_puzzle/state.h"

namespace sliding_puzzle {

class Randomizer {
 public:
    virtual std::vector<Move> shuffle(const State& state, int limit) = 0;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_RANDOMIZER_H_

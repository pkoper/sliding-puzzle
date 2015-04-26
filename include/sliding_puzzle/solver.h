#ifndef INCLUDE_SLIDING_PUZZLE_SOLVER_H_
#define INCLUDE_SLIDING_PUZZLE_SOLVER_H_

#include <vector>

#include "sliding_puzzle/move.h"
#include "sliding_puzzle/state.h"

namespace sliding_puzzle {

class Solver {
 public:
    virtual void init(const State& goal) = 0;
    virtual void record(Move move) = 0;
    virtual std::vector<Move> resolve(const State& start, int timeout) = 0;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_SOLVER_H_

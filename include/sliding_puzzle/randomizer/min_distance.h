#ifndef INCLUDE_SLIDING_PUZZLE_RANDOMIZER_MIN_DISTANCE_H_
#define INCLUDE_SLIDING_PUZZLE_RANDOMIZER_MIN_DISTANCE_H_

#include <vector>

#include "sliding_puzzle/randomizer.h"

namespace sliding_puzzle {
namespace randomizer {

template<int N>
class MinDistance : public Randomizer {
 public:
    std::vector<Move> shuffle(const State& start, int limit) override {
        State state(start);
        std::vector<Move> moves;
        auto random_move = move::random();
        Move last_move = Move::NONE;
        int i = 0;
        while (i < limit) {
            Move move = random_move();
            if (move != move::inverse(last_move)) {
                if (state.applyMove(move)) {
                    moves.push_back(move);
                    last_move = move;
                    if (state.getMinDistanceTo(start) >= N) {
                        break;
                    }
                    i++;
                }
            }
        }
        return moves;
    }
};

}  // namespace randomizer
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_RANDOMIZER_MIN_DISTANCE_H_

#ifndef INCLUDE_SLIDING_PUZZLE_MOVE_H_
#define INCLUDE_SLIDING_PUZZLE_MOVE_H_

#include <algorithm>
#include <chrono>
#include <functional>
#include <random>
#include <vector>

namespace sliding_puzzle {

enum class Move : int {
    DOWN  = -2,
    LEFT  = -1,
    NONE  =  0,
    RIGHT =  1,
    UP    =  2,
};

namespace move {

inline Move inverse(Move move) {
    return static_cast<Move>(- static_cast<int>(move));
}

inline std::function <Move()> random() {
    auto now = std::chrono::high_resolution_clock::now();
    auto seed = now.time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0, 3);
    auto to_move = [](int r) -> Move {
        switch (r) {
            case 0: return Move::LEFT;
            case 1: return Move::UP;
            case 2: return Move::RIGHT;
            case 3: return Move::DOWN;
        }
        return Move::NONE;
    };
    return std::bind(to_move, std::bind(distribution, generator));
}

inline std::vector<Move> undo(const std::vector<Move>& input) {
    std::vector<Move> output(input.size());
    std::transform(input.begin(), input.end(), output.begin(), move::inverse);
    std::reverse(output.begin(), output.end());
    return output;
}

}  // namespace move
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_MOVE_H_

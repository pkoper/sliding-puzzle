#ifndef INCLUDE_SLIDING_PUZZLE_SOLVER_PLAYBACK_H_
#define INCLUDE_SLIDING_PUZZLE_SOLVER_PLAYBACK_H_

#include <SFML/System/Time.hpp>

#include <utility>
#include <vector>

#include "sliding_puzzle/pair.h"

namespace sliding_puzzle {
namespace solver {

class Playback : public Solver {
 public:
    void init(const State& goal) override {
        m_goal = goal;
        reset();
    }

    void record(Move move) override {
        m_state.applyMove(move);
        m_track.push_back({move, m_state});
    }

    std::vector<Move> resolve(const State& start, int timeout) override {
        unused::params(start, timeout);
        auto serious_walks = removeSillyWalks(m_track);
        auto moves = pair::first(serious_walks);
        auto undo_moves = move::undo(moves);
        reset();
        return undo_moves;
    }

 protected:
    void reset() {
        m_state = m_goal;
        m_track.clear();
        m_track.push_back({Move::NONE, m_state});
    }

    // The Ministry of Silly Walks
    std::vector<std::pair<Move, State>> removeSillyWalks(
                const std::vector<std::pair<Move, State>>& input) {
        std::vector<std::pair<Move, State>> track(input);
        for (size_t i = 0; i < track.size();) {
            bool found = false;
            for (size_t j = track.size() - 1; j > i; j--) {
                State& i_state = track[i].second;
                State& j_state = track[j].second;
                if (i_state == j_state) {
                    track.erase(track.begin() + i + 1, track.begin() + j + 1);
                    found = true;
                    break;
                }
            }
            if (!found) {
                i++;
            }
        }
        return track;
    }

    State m_goal;
    State m_state;
    std::vector<std::pair<Move, State>> m_track;
};

}  // namespace solver
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_SOLVER_PLAYBACK_H_

#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_SOLVABLE_GAME_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_SOLVABLE_GAME_H_

#include <algorithm>
#include <deque>
#include <utility>
#include <vector>

#include "sliding_puzzle/component/shuffleable_game.h"
#include "sliding_puzzle/solver.h"

namespace sliding_puzzle {
namespace component {

class SolvableGame : public ShuffleableGame {
 public:
    SolvableGame(const std::vector<sf::String>& paths, double margin,
                    double tile_margin, int size, int size_min, int size_max,
                    int animation_speed, CoordinateConverter *converter,
                    std::vector<std::pair<Randomizer*, int>> randomizers,
                    std::vector<std::pair<Solver*, int>> solvers) :
            ShuffleableGame(paths, margin, tile_margin, size, size_min,
                            size_max, animation_speed, converter, randomizers),
            m_solvers(solvers)
     {}

    void create() override {
        ShuffleableGame::create();
        m_goal = m_state;
        init(m_goal);
    }

    bool handleEvent(const sf::Event& event) override {
        if (m_playing) {
            return false;
        }
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::S:
                solve();
                return true;
            default:
                break;
            }
        }
        return ShuffleableGame::handleEvent(event);
    }

    bool move(Move move) override {
        auto valid = ShuffleableGame::move(move);
        if (m_recording && valid) {
            for (auto& pair : m_solvers) {
                auto solver = pair.first;
                solver->record(move);
            }
        }
        return valid;
    }

    void solve() {
        std::vector<Move> moves;
        for (auto& pair : m_solvers) {
            auto solver = pair.first;
            auto timeout = pair.second;
            moves = solver->resolve(m_state, timeout);
            if (!moves.empty()) {
                break;
            }
        }
        play(moves);
        init(m_goal);
    }

    void play(const std::vector<Move>& moves) {
        m_playing = true;
        m_recording = false;
        m_playback_moves.clear();
        std::copy(moves.begin(), moves.end(),
                  std::inserter(m_playback_moves, m_playback_moves.end()));
    }

    void animate() override {
        ShuffleableGame::animate();
        if (!m_animating) {
            if (!m_playback_moves.empty()) {
                move(m_playback_moves.front());
                m_playback_moves.pop_front();
            } else {
                m_playing = false;
                m_recording = true;
            }
        }
    }

 protected:
    void init(const State& state) {
        for (auto& pair : m_solvers) {
            auto solver = pair.first;
            solver->init(state);
        }
    }

    std::vector<std::pair<Solver*, int>> m_solvers;
    std::deque<Move> m_playback_moves;
    bool m_playing = false;
    bool m_recording = true;
    State m_goal;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_SOLVABLE_GAME_H_

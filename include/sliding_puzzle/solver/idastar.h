#ifndef INCLUDE_SLIDING_PUZZLE_SOLVER_IDASTAR_H_
#define INCLUDE_SLIDING_PUZZLE_SOLVER_IDASTAR_H_

#include <SFML/System/Clock.hpp>

#include <vector>

#include "sliding_puzzle/solver.h"
#include "sliding_puzzle/unused.h"

namespace sliding_puzzle {
namespace solver {

class IDAStar : public Solver {
 public:
    struct Node {
        State state;
        int cost = 0;
        Move origin = Move::NONE;
    };

    void init(const State& goal) override {
        m_goal = goal;
    }

    void record(Move move) override {
        unused::params(move);
    }

    std::vector<Move> resolve(const State& start, int timeout_ms) override {
        m_clock.restart();
        auto timeout = sf::milliseconds(timeout_ms);
        Node node;
        node.state = start;
        int next_cost_bound = start.getDistanceTo(m_goal);
        std::vector<Move> solution;
        do {
            if (m_clock.getElapsedTime() > timeout) {
                return {};
            }
            solution = depthFirstSearch(node, next_cost_bound, m_goal,
                                        timeout);
            next_cost_bound += 2;
        } while (solution.empty());
        std::reverse(solution.begin(), solution.end());
        return solution;
    }

 protected:
    std::vector<Move> depthFirstSearch(const Node& current, int cost_bound,
                                       const State& goal, sf::Time timeout) {
        if (current.state == goal) {
            return {current.origin};
        }

        if (m_clock.getElapsedTime() > timeout) {
            return {};
        }

        auto children = getChildren(current);
        for (auto& child : children) {
            int cost = child.cost + child.state.getDistanceTo(m_goal);
            if (cost <= cost_bound) {
                std::vector<Move> result = depthFirstSearch(child, cost_bound,
                                                            m_goal, timeout);
                if (!result.empty()) {
                    result.push_back(child.origin);
                    return result;
                }
            }
        }
        return {};
    }

    std::vector<Node> getChildren(const Node& node) {
        std::vector<Node> children;
        std::vector<Move> moves = node.state.getPossibleMoves();
        for (auto& move : moves) {
            if (move != move::inverse(node.origin)) {
                Node child;
                child.origin = move;
                child.state = node.state;
                child.state.applyMove(move);
                child.cost = node.cost + 1;
                children.push_back(std::move(child));
            }
        }
        return children;
    }

    State m_goal;
    sf::Clock m_clock;
};

}  // namespace solver
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_SOLVER_IDASTAR_H_

#ifndef INCLUDE_SLIDING_PUZZLE_STATE_H_
#define INCLUDE_SLIDING_PUZZLE_STATE_H_

#include <algorithm>
#include <vector>

#include "sliding_puzzle/move.h"

namespace sliding_puzzle {

class State {
 public:
    State() {}

    State(const State& other) :
            m_size(other.m_size), m_elements(other.m_elements) {
        auto position = other.m_active - other.m_elements.begin();
        m_active = m_elements.begin() + position;
    }

    State(State&& other) noexcept :
            m_size(other.m_size), m_elements(other.m_elements) {
        auto position = other.m_active - other.m_elements.begin();
        m_active = m_elements.begin() + position;
    }

    State& operator=(const State& other) {
        State object(other);
        *this = std::move(object);
        return *this;
    }

    State& operator=(State&& other) noexcept {
        auto position = m_active - m_elements.begin();
        auto other_position = other.m_active - other.m_elements.begin();
        std::swap(m_size, other.m_size);
        std::swap(m_elements, other.m_elements);
        std::swap(position, other_position);
        m_active = m_elements.begin() + position;
        other.m_active = other.m_elements.begin() + other_position;
        return *this;
    }

    ~State() noexcept {}

    bool operator==(const State& rhs) const {
        auto position = m_active - m_elements.begin();
        auto rhs_position = rhs.m_active - rhs.m_elements.begin();
        return (position == rhs_position) && (m_elements == rhs.m_elements);
    }

    void create(int size) {
        m_size = size;
        m_elements.clear();
        m_elements.resize(size * size);
        std::iota(m_elements.begin(), m_elements.end(), 0);
        m_active = m_elements.end() - 1;
    }

    int getSize() const { return m_size; }
    int getActiveElement() const { return *m_active; }
    std::vector<int> getElements() const { return m_elements; }

    std::vector<Move> getPossibleMoves() const {
        std::vector<Move> moves;
        auto index = m_active - m_elements.begin();
        auto row = index / m_size;
        auto col = index % m_size;
        if (col < m_size - 1) {
            moves.push_back(Move::LEFT);
        }
        if (row < m_size - 1) {
            moves.push_back(Move::UP);
        }
        if (col > 0) {
            moves.push_back(Move::RIGHT);
        }
        if (row > 0) {
            moves.push_back(Move::DOWN);
        }
        return moves;
    }

    bool applyMove(Move move) {
        auto index = m_active - m_elements.begin();
        auto row = index / m_size;
        auto col = index % m_size;
        switch (move) {
        case Move::LEFT:
            if (col < m_size - 1) {
                swapActiveWith(m_active + 1);
                return true;
            }
            break;
        case Move::UP:
            if (row < m_size - 1) {
                swapActiveWith(m_active + m_size);
                return true;
            }
            break;
        case Move::RIGHT:
            if (col > 0) {
                swapActiveWith(m_active - 1);
                return true;
            }
            break;
        case Move::DOWN:
            if (row > 0) {
                swapActiveWith(m_active - m_size);
                return true;
            }
            break;
        default:
            break;
        }
        return false;
    }

    Move findMove(int i) const {
        auto index = m_elements.begin() + i;
        if (index == m_active + 1) {
            return Move::LEFT;
        } else if (index == m_active + m_size) {
            return Move::UP;
        } else if (index == m_active - 1) {
            return Move::RIGHT;
        } else if (index == m_active - m_size) {
            return Move::DOWN;
        }
        return Move::NONE;
    }

    int getDistanceTo(const State& other) const {
        int total = 0;
        int size = m_elements.size();
        for (int i = 0; i < size; i++) {
            if (m_elements[i] == other.m_elements[i]) {
                continue;
            }
            auto index = std::find(m_elements.begin(), m_elements.end(),
                                   other.m_elements[i]);
            int position = index - m_elements.begin();
            total += getDistance(position, i);
        }
        return total;
    }

    int getMinDistanceTo(const State& other) const {
        int min_distance = 2 * (m_size - 1);
        for (int i = 0; i < m_size; i++) {
            if (m_elements[i] == other.m_elements[i]) {
                return 0;
            }
            auto index = std::find(m_elements.begin(), m_elements.end(),
                                   other.m_elements[i]);
            int position = index - m_elements.begin();
            int distance = getDistance(position, i);
            if (distance < min_distance) {
                min_distance = distance;
            }
        }
        return min_distance;
    }

    int getDistance(int a, int b) const {
        int a_row = a / m_size;
        int a_col = a % m_size;
        int b_row = b / m_size;
        int b_col = b % m_size;
        return std::abs(b_row - a_row) + std::abs(b_col - a_col);
    }

 protected:
    void swapActiveWith(typename std::vector<int>::iterator neighbour) {
        std::iter_swap(m_active, neighbour);
        m_active = neighbour;
    }

    int m_size = 0;
    typename std::vector<int>::iterator m_active;
    std::vector<int> m_elements;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_STATE_H_

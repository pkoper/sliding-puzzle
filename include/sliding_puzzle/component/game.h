#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_GAME_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_GAME_H_

#include <vector>

#include "sliding_puzzle/component/matrix.h"
#include "sliding_puzzle/coordinate_converter.h"
#include "sliding_puzzle/state.h"

namespace sliding_puzzle {
namespace component {

class Game : public Matrix {
 public:
    Game(const std::vector<sf::String>& paths, double margin,
         double tile_margin, int size, int size_min, int size_max,
         int animation_speed, CoordinateConverter* converter) :
            Matrix(paths, margin, tile_margin, size, size_min, size_max),
            m_animation_speed(animation_speed),
            m_converter(converter) {}

    void create() override {
        Matrix::create();
        m_state.create(m_size);
        m_tiles[m_state.getActiveElement()]->setVisible(false);
    }

    bool handleEvent(const sf::Event& event) override {
        switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::Left:
                move(Move::LEFT);
                return true;
            case sf::Keyboard::Up:
                move(Move::UP);
                return true;
            case sf::Keyboard::Right:
                move(Move::RIGHT);
                return true;
            case sf::Keyboard::Down:
                move(Move::DOWN);
                return true;
            default:
                break;
            }
        case sf::Event::MouseButtonPressed:
            {
                auto mouse = event.mouseButton;
                switch (mouse.button) {
                case sf::Mouse::Left:
                    move(sf::Vector2i(mouse.x, mouse.y));
                    return true;
                default:
                    break;
                }
            }
        default:
            break;
        }
        return Matrix::handleEvent(event);
    }

    virtual bool move(Move move) {
        bool success = m_state.applyMove(move);
        if (success) {
            applyState(m_state);
        }
        return success;
    }

    virtual bool move(const sf::Vector2i& point) {
        auto cords = m_converter->mapPixelToCoords(point, m_view);
        Slot *slot = getSlot(cords);
        if (slot != nullptr) {
            int clicked = slot->getId();
            return move(m_state.findMove(clicked));
        }
        return false;
    }

    void render(sf::RenderWindow* renderWindow) override {
        animate();
        Matrix::render(renderWindow);
    }

    virtual void animate() {
        sf::Time frame_time = m_frame_clock.restart();
        m_current_time += frame_time;
        double delta = m_current_time.asMilliseconds();
        m_animation_factor = delta / m_animation_speed;
        int step = m_animation_factor * m_tile_size;
        m_current_time = sf::Time::Zero;
        int total_distance = 0;
        for (auto& slot : m_slots) {
            auto tile = slot.getTile();
            auto offset = stepOffset(tile->getPosition(),
                                     slot.getPosition(), step);
            tile->move(offset);
            total_distance += distance(offset, sf::Vector2f(0, 0));
        }
        m_animating = (total_distance != 0);
    }

 protected:
    Slot* getSlot(const sf::Vector2f& cords) {
        for (auto& slot : m_slots) {
            if (isSlotPoint(slot, cords)) {
                return &slot;
            }
        }
        return nullptr;
    }

    bool isSlotPoint(const Slot& slot, const sf::Vector2f& cords) {
        auto position = slot.getPosition();
        return ((cords.x >= position.x) &&
                (cords.x <= position.x + m_tile_size) &&
                (cords.y >= position.y) &&
                (cords.y <= position.y + m_tile_size));
    }

    void applyState(const State& state) {
        auto elements = state.getElements();
        for (int slot_index = 0; slot_index < m_size * m_size; slot_index++) {
            Slot& slot = m_slots[slot_index];
            Tile* tile = m_tiles[elements[slot_index]].get();
            slot.setTile(tile);
        }
    }

    template<typename T>
    int distance(const T& a, const T& b) {
        return std::abs(b.x - a.x) + std::abs(b.y - a.y);
    }

    sf::Vector2f stepOffset(const sf::Vector2f& a,
                            const sf::Vector2f& b, int step) {
        sf::Vector2f offset(b.x - a.x, b.y - a.y);
        return limitOffset(offset, step);
    }

    sf::Vector2f limitOffset(const sf::Vector2f& offset, int limit) {
        auto x = offset.x > limit ? limit : offset.x < -limit ?
                    -limit : offset.x;
        auto y = offset.y > limit ? limit : offset.y < -limit ?
                    -limit : offset.y;
        return sf::Vector2f(x, y);
    }

    bool m_animating = true;
    int m_animation_speed;
    double m_animation_factor;
    sf::Clock m_frame_clock;
    sf::Time m_current_time;
    State m_state;
    CoordinateConverter *m_converter;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_GAME_H_

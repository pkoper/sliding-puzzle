#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_SHUFFLEABLE_GAME_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_SHUFFLEABLE_GAME_H_

#include <utility>
#include <vector>

#include "sliding_puzzle/randomizer.h"
#include "sliding_puzzle/component/game.h"

namespace sliding_puzzle {
namespace component {

class ShuffleableGame : public Game {
 public:
    ShuffleableGame(const std::vector<sf::String>& paths, double margin,
                    double tile_margin, int size, int size_min, int size_max,
                    int animation_speed, CoordinateConverter *converter,
                    std::vector<std::pair<Randomizer*, int>> randomizers) :
            Game(paths, margin, tile_margin, size, size_min, size_max,
                 animation_speed, converter),
            m_randomizers(randomizers)
     {}

    void create() override {
        Game::create();
        m_tiles[m_state.getActiveElement()]->setVisible(false);
    }

    bool handleEvent(const sf::Event& event) override {
        switch (event.type) {
        case sf::Event::KeyPressed:
            switch (event.key.code) {
            case sf::Keyboard::R:
            case sf::Keyboard::Space:
                shuffle();
                return true;
            default:
                break;
            }
        default:
            break;
        }
        return Game::handleEvent(event);
    }

 protected:
    void shuffle() {
        for (auto& pair : m_randomizers) {
            auto randomizer = pair.first;
            auto limit = pair.second;
            auto moves = randomizer->shuffle(m_state, limit);
            for (auto step : moves) {
               move(step);
            }
        }
    }

    std::vector<std::pair<Randomizer*, int>> m_randomizers;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_SHUFFLEABLE_GAME_H_

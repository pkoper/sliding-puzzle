#ifndef INCLUDE_SLIDING_PUZZLE_COORDINATE_CONVERTER_H_
#define INCLUDE_SLIDING_PUZZLE_COORDINATE_CONVERTER_H_

#include <SFML/Graphics.hpp>

namespace sliding_puzzle {

class CoordinateConverter {
 public:
    virtual sf::Vector2f mapPixelToCoords(const sf::Vector2i& point,
                                          const sf::View& view) = 0;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COORDINATE_CONVERTER_H_

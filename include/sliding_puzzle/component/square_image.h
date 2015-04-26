#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_SQUARE_IMAGE_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_SQUARE_IMAGE_H_

#include <vector>

#include "sliding_puzzle/component/image.h"

namespace sliding_puzzle {
namespace component {

class SquareImage : public Image {
 public:
    SquareImage(const std::vector<sf::String>& paths, double margin) :
            Image(paths, margin) {}

    void layout(const sf::Vector2u& size) override {
      m_view.setViewport(getViewportRect(size));
    }

 protected:
    sf::FloatRect getTextureRect() override {
        auto size = m_texture.getSize();
        sf::FloatRect rect;
        if (size.y > size.x) {
            rect.width = size.x;
            rect.height = size.x;
            rect.top = (size.y - rect.height) / 2;
            rect.left = 0;
        } else {
            rect.width = size.y;
            rect.height = size.y;
            rect.top = 0;
            rect.left = (size.x - rect.width) / 2;
        }
        return rect;
    }

    virtual sf::FloatRect getViewportRect(const sf::Vector2u& size) {
        sf::FloatRect rect;
        if (size.x > size.y) {
            rect.top = m_margin;
            rect.height = 1 - (2 * m_margin);
            rect.width = (rect.height * size.y) / size.x;
            rect.left = (1 - rect.width) / 2;
        } else {
            rect.left = m_margin;
            rect.width = 1 - (2 * m_margin);
            rect.height = (rect.width * size.x) / size.y;
            rect.top = (1 - rect.height) / 2;
        }
        return rect;
    }
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_SQUARE_IMAGE_H_

#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_IMAGE_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_IMAGE_H_

#include <exception>
#include <vector>

#include "sliding_puzzle/component.h"

namespace sliding_puzzle {
namespace component {

class Image : public Component {
 public:
    class LoadException : public std::exception {};

    Image(const std::vector<sf::String>& paths, double margin) :
            m_margin(margin), m_paths(paths) {}

    void init() override {
        load();
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::I:
                m_index = (m_index + 1) % m_paths.size();
                load();
                return true;
            default:
                break;
            }
        }
        return Component::handleEvent(event);
    }

    virtual void load() {
        if (!m_texture.loadFromFile(m_paths[m_index])) {
            throw LoadException();
        }
        m_sprite.setTexture(m_texture);
        m_view.reset(getTextureRect());
    }

    void render(sf::RenderWindow* renderWindow) override {
        renderWindow->setView(m_view);
        renderWindow->draw(m_sprite);
        renderWindow->setView(renderWindow->getDefaultView());
    }

 protected:
    virtual sf::FloatRect getTextureRect() {
        auto size = m_texture.getSize();
        return sf::FloatRect(0, 0, size.x, size.y);
    }

    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::View m_view;
    int m_index = 0;
    double m_margin;
    std::vector<sf::String> m_paths;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_IMAGE_H_

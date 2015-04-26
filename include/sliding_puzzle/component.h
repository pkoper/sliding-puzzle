#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_H_

#include "sliding_puzzle/window.h"
#include "sliding_puzzle/unused.h"

namespace sliding_puzzle {

class Component : public Window::Renderable {
 public:
    Component() {}
    explicit Component(bool visible) : m_visible(visible) {}
    virtual void init() {}
    virtual bool handleEvent(const sf::Event& event) {
        unused::params(event);
        return false;
    }
    virtual void layout(const sf::Vector2u& size) {
        unused::params(size);
    }
    virtual void render(sf::RenderWindow* renderWindow) {
        unused::params(renderWindow);
    }
    bool isVisible() { return m_visible; }
    void setVisible(bool visible) { m_visible = visible; }
    virtual ~Component() {}
 protected:
    bool m_visible = true;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_H_

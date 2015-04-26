#ifndef INCLUDE_SLIDING_PUZZLE_APP_H_
#define INCLUDE_SLIDING_PUZZLE_APP_H_

#include <SFML/Graphics.hpp>

#include <memory>
#include <deque>

#include "sliding_puzzle/window.h"
#include "sliding_puzzle/component.h"
#include "sliding_puzzle/coordinate_converter.h"

namespace sliding_puzzle {

class App : public Window::EventHandler, public Window::Renderable,
        public CoordinateConverter {
 public:
    App() {}

    virtual void run() {
        m_window.setEventProcessor(this);
        m_window.setRenderable(this);
        m_window.create();
        init();
        layout();
        m_window.eventLoop();
    }

    void init() {
        for (auto& component : m_components) {
            component->init();
        }
    }

    virtual void layout() {
        auto size = m_window.getSize();
        for (auto& component : m_components) {
            component->layout(size);
        }
    }

    void handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::Resized) {
            layout();
        } else {
            for (auto& component : m_components) {
                if (component->handleEvent(event)) {
                    return;
                }
            }
        }
    }

    void render(sf::RenderWindow* renderWindow) override {
        for (auto& component : m_components) {
            if (component->isVisible()) {
                component->render(renderWindow);
            }
        }
    }

    sf::Vector2f mapPixelToCoords(const sf::Vector2i& point,
                                  const sf::View& view) override {
        return m_window.mapPixelToCoords(point, view);
    }

    virtual ~App() {}
 protected:
    Window m_window;
    std::deque<std::unique_ptr<Component>> m_components;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_APP_H_

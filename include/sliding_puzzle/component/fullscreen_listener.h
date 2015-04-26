#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_FULLSCREEN_LISTENER_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_FULLSCREEN_LISTENER_H_

#include "sliding_puzzle/component.h"

namespace sliding_puzzle {
namespace component {

class FullscreenListener : public Component {
 public:
    class FullscreenHandler {
     public:
        virtual void handleFullscreen() = 0;
    };

    explicit FullscreenListener(FullscreenHandler* fullscreen_handler) :
            Component(false), m_fullscreen_handler(fullscreen_handler) {}

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::F11:
            case sf::Keyboard::F:
                m_fullscreen_handler->handleFullscreen();
                return true;
            default:
                break;
            }
        }
        return false;
    }

 protected:
    FullscreenHandler *m_fullscreen_handler;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_FULLSCREEN_LISTENER_H_

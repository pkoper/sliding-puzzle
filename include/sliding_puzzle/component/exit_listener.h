#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_EXIT_LISTENER_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_EXIT_LISTENER_H_

#include "sliding_puzzle/component.h"

namespace sliding_puzzle {
namespace component {

class ExitListener : public Component {
 public:
    class ExitHandler {
     public:
        virtual void handleExit() = 0;
    };

    explicit ExitListener(ExitHandler* exit_handler) :
            Component(false), m_exit_handler(exit_handler) {}

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Escape:
            case sf::Keyboard::Q:
                m_exit_handler->handleExit();
                return true;
            default:
                break;
            }
        }
        return false;
    }

 protected:
    ExitHandler *m_exit_handler;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_EXIT_LISTENER_H_

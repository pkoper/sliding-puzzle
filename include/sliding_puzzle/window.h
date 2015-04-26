#ifndef INCLUDE_SLIDING_PUZZLE_WINDOW_H_
#define INCLUDE_SLIDING_PUZZLE_WINDOW_H_

#include <algorithm>

namespace sliding_puzzle {

class Window {
 public:
    class EventHandler {
     public:
        virtual void handleEvent(const sf::Event& event) = 0;
    };

    class Renderable {
     public:
        virtual void render(sf::RenderWindow* renderWindow) = 0;
    };

    Window() {}

    void setTitle(const sf::String& title) {
        m_title = title;
    }

    void setFullscreen(bool fullscreen) {
        m_fullscreen = fullscreen;
    }

    void setRatio(double ratio) {
        m_ratio = ratio;
    }

    sf::VideoMode getDesktopWindowMode() const {
        auto desktop_mode = sf::VideoMode::getDesktopMode();
        float size = m_ratio * std::min(desktop_mode.width,
                                        desktop_mode.height);
        return sf::VideoMode(size, size);
    }

    void create() {
        auto mode = getDesktopWindowMode();
        auto style = m_fullscreen ? sf::Style::Fullscreen : sf::Style::Default;
        m_window.create(mode, m_title, style);
        m_window.setVerticalSyncEnabled(true);
    }

    void toggleFullscreen() {
        m_fullscreen = !m_fullscreen;
        create();
    }

    void setEventProcessor(EventHandler* event_listener) {
        m_event_listener = event_listener;
    }

    void setRenderable(Renderable* renderable) {
        m_renderable = renderable;
    }

    sf::Vector2u getSize() {
        return m_window.getSize();
    }

    sf::Vector2f mapPixelToCoords(const sf::Vector2i& point,
                                  const sf::View& view) const {
        return m_window.mapPixelToCoords(point, view);
    }

    void close() {
        m_window.close();
    }

    void eventLoop() {
        while (m_window.isOpen()) {
            sf::Event event;
            while (m_window.pollEvent(event)) {
                switch (event.type) {
                case sf::Event::Closed:
                    m_window.close();
                    break;
                default:
                    if (m_event_listener != nullptr) {
                        m_event_listener->handleEvent(event);
                    }
                }
            }
            m_window.clear();
            if (m_renderable != nullptr) {
                m_renderable->render(&m_window);
            }
            m_window.display();
        }
    }

 protected:
    static const sf::Uint32 STYLE_FULLSCREEN = sf::Style::Fullscreen;
    static const sf::Uint32 STYLE_DEFAULT = sf::Style::Default;

    sf::String m_title;
    bool m_fullscreen = false;
    double m_ratio = 0.5;
    sf::RenderWindow m_window;
    EventHandler *m_event_listener;
    Renderable *m_renderable;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_WINDOW_H_

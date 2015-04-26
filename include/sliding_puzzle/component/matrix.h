#ifndef INCLUDE_SLIDING_PUZZLE_COMPONENT_MATRIX_H_
#define INCLUDE_SLIDING_PUZZLE_COMPONENT_MATRIX_H_

#include <vector>

#include "sliding_puzzle/component/square_image.h"

namespace sliding_puzzle {
namespace component {

class Matrix : public SquareImage {
 public:
    class Tile : public sf::Sprite {
     public:
        Tile(int id, const sf::Vector2f& position, int size,
             const sf::Texture& texture) : m_id(id) {
            setTexture(texture);
            setTextureRect(sf::IntRect(position.x, position.y, size, size));
            setPosition(position);
        }
        int getId() const { return m_id; }
        bool isVisible() const { return m_visible; }
        void setVisible(bool visible) { m_visible = visible; }
     protected:
        int m_id;
        bool m_visible = true;
    };

    class Slot {
     public:
        Slot() {}
        Slot(int id, const sf::Vector2f& position, Tile* tile) :
            m_id(id), m_position(position), m_tile(tile) {}
        int getId() const { return m_id; }
        const sf::Vector2f getPosition() const { return m_position; }
        void setPosition(const sf::Vector2f& position) {
            m_position = position;
        }
        void setTile(Tile* tile) { m_tile = tile; }
        Tile* getTile() const { return m_tile; }
        bool operator<(const Slot& rhs) const { return m_id < rhs.m_id; }
     protected:
        const int m_id = -1;
        sf::Vector2f m_position;
        Tile* m_tile = nullptr;
    };

    Matrix(const std::vector<sf::String>& paths, double margin,
           double tile_margin, int size, int size_min, int size_max) :
            SquareImage(paths, margin), m_tile_margin(tile_margin),
            m_size(size), m_size_min(size_min), m_size_max(size_max) {}

    void load() override {
        SquareImage::load();
        create();
    }

    virtual void create() {
        m_slots.clear();
        auto texture_rect = getTextureRect();
        m_tile_size = texture_rect.width /
                        (m_size + (m_size - 1) * m_tile_margin);
        double margin_size = m_tile_margin * m_tile_size;
        int left = texture_rect.left;
        int top = texture_rect.top;
        m_slots.clear();
        m_tiles.clear();
        for (int i = 0; i < m_size * m_size; i++) {
            int row = i / m_size;
            int col = i % m_size;
            int x = left + col * (margin_size + m_tile_size);
            int y = top + row * (margin_size + m_tile_size);
            sf::Vector2f position(x, y);
            std::unique_ptr<Tile> tile(new Tile(i, position,
                                                m_tile_size,
                                                m_texture));
            Slot slot(i, position, tile.get());
            m_slots.push_back(std::move(slot));
            m_tiles.push_back(std::move(tile));
        }
    }

    bool handleEvent(const sf::Event& event) override {
        if (event.type == sf::Event::KeyPressed) {
            switch (event.key.code) {
            case sf::Keyboard::Add:
            case sf::Keyboard::K:
                if (m_size < m_size_max) {
                    m_size++;
                    create();
                }
                break;
            case sf::Keyboard::Subtract:
            case sf::Keyboard::J:
                if (m_size > m_size_min) {
                    m_size--;
                    create();
                }
                break;
            default:
                break;
            }
        }
        return SquareImage::handleEvent(event);
    }

    void render(sf::RenderWindow* renderWindow) override {
        renderWindow->setView(m_view);
        for (auto& tile : m_tiles) {
            if (tile->isVisible()) {
                renderWindow->draw(*tile);
            }
        }
        renderWindow->setView(renderWindow->getDefaultView());
    }

 protected:
    double m_tile_margin;
    double m_tile_size;
    int m_size;
    int m_size_min;
    int m_size_max;
    std::vector<Slot> m_slots;
    std::vector<std::unique_ptr<Tile>> m_tiles;
};

}  // namespace component
}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_COMPONENT_MATRIX_H_

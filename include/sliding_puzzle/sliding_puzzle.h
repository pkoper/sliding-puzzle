#ifndef INCLUDE_SLIDING_PUZZLE_SLIDING_PUZZLE_H_
#define INCLUDE_SLIDING_PUZZLE_SLIDING_PUZZLE_H_

#include <algorithm>
#include <limits>
#include <utility>
#include <string>
#include <vector>

#include "sliding_puzzle/app.h"
#include "sliding_puzzle/coordinate_converter.h"

#include "sliding_puzzle/component/exit_listener.h"
#include "sliding_puzzle/component/fullscreen_listener.h"

#include "sliding_puzzle/component/image.h"
#include "sliding_puzzle/component/square_image.h"
#include "sliding_puzzle/component/matrix.h"
#include "sliding_puzzle/component/game.h"
#include "sliding_puzzle/component/shuffleable_game.h"
#include "sliding_puzzle/component/solvable_game.h"

#include "sliding_puzzle/randomizer.h"
#include "sliding_puzzle/randomizer/min_distance.h"

#include "sliding_puzzle/solver.h"
#include "sliding_puzzle/solver/idastar.h"
#include "sliding_puzzle/solver/playback.h"

namespace sliding_puzzle {

class SlidingPuzzle :
        public App, public component::ExitListener::ExitHandler,
        public component::FullscreenListener::FullscreenHandler {
 public:
    struct Config {
        std::string title = "SLIDING PUZZLE";
        int size = 5;
        int size_min = 2;
        int size_max = 7;
        bool fullscreen = false;
        double window_ratio = 0.6;
        double window_margin = 0.1;
        double tile_margin = 0.05;
        int animation_speed = 500;
        int solver_limit = 3000;
        std::vector<sf::String> images;
        std::vector<std::pair<std::unique_ptr<Randomizer>, int>> randomizers;
        std::vector<std::pair<std::unique_ptr<Solver>, int>> solvers;
    };

    class Creator {
     public:
        Creator& setTitle(sf::String title) {
            m_config.title = title;
            return *this;
        }
        Creator& setSize(int size) {
            m_config.size = size;
            return *this;
        }
        Creator& setSizeMin(int size_min) {
            m_config.size_min = size_min;
            return *this;
        }
        Creator& setSizeMax(int size_max) {
            m_config.size_max = size_max;
            return *this;
        }
        Creator& setFullscreen(bool fullscreen) {
            m_config.fullscreen = fullscreen;
            return *this;
        }
        Creator& setWindowRatio(double window_ratio) {
            m_config.window_ratio = window_ratio;
            return *this;
        }
        Creator& setWindowMargin(double window_margin) {
            m_config.window_margin = window_margin;
            return *this;
        }
        Creator& setTileMargin(double tile_margin) {
            m_config.tile_margin = tile_margin;
            return *this;
        }
        Creator& setAnimationSpeed(int animation_speed) {
            m_config.animation_speed = animation_speed;
            return *this;
        }
        Creator& addImage(const sf::String& path) {
            m_config.images.push_back(path);
            return *this;
        }
        Creator& addRandomizerWithLimit(std::unique_ptr<Randomizer> randomizer,
                                        int limit) {
            m_config.randomizers.push_back({std::move(randomizer), limit});
            return *this;
        }
        Creator& addSolverWithTimeout(std::unique_ptr<Solver> solver,
                                      int timeout) {
            m_config.solvers.push_back({std::move(solver), timeout});
            return *this;
        }
        Creator& addSolver(std::unique_ptr<Solver> solver) {
            int timeout = std::numeric_limits<int>::max();
            return addSolverWithTimeout(std::move(solver), timeout);
        }
        std::unique_ptr<App> create() {
            return std::unique_ptr<App>(new SlidingPuzzle(std::move(m_config)));
        }

     protected:
        Config m_config;
    };

    std::unique_ptr<Creator> creator() {
        return std::unique_ptr<Creator>(new Creator());
    }

    explicit SlidingPuzzle(Config&& config) : m_config(std::move(config)) {
        extract_ptrs(&m_config.randomizers, &m_randomizers);
        extract_ptrs(&m_config.solvers, &m_solvers);
    }

    void run() override {
        m_window.setTitle(m_config.title);
        m_window.setRatio(m_config.window_ratio);
        m_window.setFullscreen(m_config.fullscreen);

        m_components.clear();
        m_components.push_back(std::unique_ptr<Component>(
            new component::ExitListener(this)));
        m_components.push_back(std::unique_ptr<Component>(
            new component::FullscreenListener(this)));

    /*
        m_components.push_back(std::unique_ptr<Component>(
            new component::Image(m_config.images, m_config.window_margin)));
     */
    /*
        m_components.push_back(std::unique_ptr<Component>(
            new component::SquareImage(m_config.images, m_config.window_margin)));
     */
    /*
        m_components.push_back(std::unique_ptr<Component>(
            new component::Matrix(m_config.images, m_config.window_margin,
                m_config.tile_margin, m_config.size, m_config.size_min,
                m_config.size_max)));
     */
    /*
        m_components.push_back(std::unique_ptr<Component>(
            new component::Game(m_config.images, m_config.window_margin,
                m_config.tile_margin, m_config.size, m_config.size_min,
                m_config.size_max, m_config.animation_speed, this)));
     */
    /*
        m_components.push_back(std::unique_ptr<Component>(
            new component::ShuffleableGame(m_config.images, m_config.window_margin,
                m_config.tile_margin, m_config.size, m_config.size_min,
                m_config.size_max, m_config.animation_speed, this,
                m_randomizers)));
    */
        m_components.push_back(std::unique_ptr<Component>(
            new component::SolvableGame(m_config.images, m_config.window_margin,
                m_config.tile_margin, m_config.size, m_config.size_min,
                m_config.size_max, m_config.animation_speed, this,
                m_randomizers, m_solvers)));

         App::run();
    }

    void handleExit() override {
        m_window.close();
    }

    void handleFullscreen() override {
        m_window.toggleFullscreen();
        layout();
    }

 protected:
    template<typename T>
    static std::pair<T*, int> pair_extract_ptr(
            const std::pair<std::unique_ptr<T>, int>& pair) {
        return {pair.first.get(), pair.second};
    }

    template<typename T, typename Second>
    void extract_ptrs(
            std::vector<std::pair<std::unique_ptr<T>, Second>> *unique_ptrs,
                       std::vector<std::pair<T*, Second>> *ptrs) {
        ptrs->resize(unique_ptrs->size());
        std::transform(unique_ptrs->begin(), unique_ptrs->end(), ptrs->begin(),
                       pair_extract_ptr<T>);
    }

    Config m_config;
    std::vector<std::pair<Randomizer*, int>> m_randomizers;
    std::vector<std::pair<Solver*, int>> m_solvers;
};

}  // namespace sliding_puzzle

#endif  // INCLUDE_SLIDING_PUZZLE_SLIDING_PUZZLE_H_

#include "sliding_puzzle/sliding_puzzle.h"

int main() {
    std::unique_ptr<sliding_puzzle::Randomizer> distance1(
        new sliding_puzzle::randomizer::MinDistance<1>());
    std::unique_ptr<sliding_puzzle::Randomizer> distance2(
        new sliding_puzzle::randomizer::MinDistance<2>());

    std::unique_ptr<sliding_puzzle::Solver> idastar(
        new sliding_puzzle::solver::IDAStar());
    std::unique_ptr<sliding_puzzle::Solver> playback(
        new sliding_puzzle::solver::Playback());

    auto app = sliding_puzzle::SlidingPuzzle::Creator()
        .setTitle("Sliding Puzzle")
        .setSize(4)
        .setSizeMin(3)
        .setSizeMax(6)
        .addRandomizerWithLimit(std::move(distance2), 151)
        .addRandomizerWithLimit(std::move(distance1), 491)
        .addSolverWithTimeout(std::move(idastar), 2000)
        .addSolver(std::move(playback))
        .setFullscreen(false)
        .setWindowRatio(0.6)
        .setWindowMargin(0.07)
        .setTileMargin(0.05)
        .setAnimationSpeed(50)
        .addImage("data/eiffel.jpg")
        .addImage("data/city.jpg")
        .addImage("data/boat.jpg")
        .create();
    app->run();
}

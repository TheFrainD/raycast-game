#include "core/game.h"

namespace core {

Game::Game() {}

Game::~Game() {}

void Game::Run() {
    window_ = std::make_unique<Window>(640, 480, "Raytracer game");

    running_ = true;

    while (running_) {
        Window::PollEvents();
        running_ = window_->IsOpen();

        window_->SwapBuffers();
    }
}

}  // namespace core
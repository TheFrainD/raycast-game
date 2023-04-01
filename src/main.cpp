#include <iostream>

#include "core/game.h"

int main() {
    core::Game game;

    try {
        game.Run();
    } catch (const std::exception& e) {
        std::cerr << e.what();
    }

    return 0;
}
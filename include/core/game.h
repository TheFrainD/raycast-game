#pragma once

namespace core {

class Game final {
public:
    Game();
    ~Game();

    Game(const Game &)            = delete;
    Game(Game &&)                 = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&)      = delete;

    void Run();

private:
    bool running_ {};
};

}  // namespace core
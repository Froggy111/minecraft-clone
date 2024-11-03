module;
#include <functional>

export module game_engine;

export namespace game_engine {
  class GameEngine {
  public:
    GameEngine();
    ~GameEngine();
    bool add_hook(std::function<void(void)> func);
  };
}
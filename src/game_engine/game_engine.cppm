module;

export module game_engine;

export namespace game_engine {
  class GameEngine {
  public:
    GameEngine();
    ~GameEngine();
    void hello();
    void hello2();
    void hello3();
  };
}

void game_engine::GameEngine::hello3() {
  return;
}
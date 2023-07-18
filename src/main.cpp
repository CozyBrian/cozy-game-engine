#include "Game.hpp"

Game *game = nullptr;

int main(int argc, char const *argv[]) {
  game = new Game();

  game->init("Game Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, true);

  while (game->running()) {
    game->handleEvents();
    game->update();
    game->render();
  }
  
  game->clean();

  return EXIT_SUCCESS; 
}
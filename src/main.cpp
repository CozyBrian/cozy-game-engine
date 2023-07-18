#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char const *argv[])
{
  int SCREEN_WIDTH = 800;
  int SCREEN_HEIGHT = 600;

  SDL_Window *window = nullptr;
  SDL_Renderer *renderer = nullptr;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
      std::cout << "SDL could not be initialized: " << SDL_GetError();
  } else {
      std::cout << "SDL video system is ready to go\n";
  }

  window = SDL_CreateWindow(
    "My First Window", 
    SDL_WINDOWPOS_CENTERED, 
    SDL_WINDOWPOS_CENTERED, 
    SCREEN_WIDTH, 
    SCREEN_HEIGHT, 
    SDL_WINDOW_SHOWN |
    SDL_WINDOW_METAL
    );
  if (window == NULL) {
      // In the case that the window could not be made...
      printf("Could not create window: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == NULL) {
      // In the case that the renderer could not be made...
      printf("Could not create renderer: %s\n", SDL_GetError());
      return EXIT_FAILURE;
  } 

  SDL_SetRenderDrawColor(renderer, 92, 154, 212, 255);
  SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);

  SDL_Delay(10 * 1000);

  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  printf("Exiting....\n");
  SDL_Quit();


  return EXIT_SUCCESS; 
}
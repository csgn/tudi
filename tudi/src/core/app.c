#include "app.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <stdio.h>
#include <stdlib.h>

Application AppInstance;

static void destroy_application(bool exit_status) {
  if (AppInstance.m_window) {
    // log info
    SDL_DestroyWindow(AppInstance.m_window);
  }

  if (AppInstance.m_renderer) {
    // log info
    SDL_DestroyRenderer(AppInstance.m_renderer);
  }

  AppInstance.m_running = false;

  SDL_Quit();
  exit(exit_status);
}

static void run_application() {
  // log info

  SDL_Event m_event;
  while (AppInstance.m_running) {
    SDL_SetRenderDrawColor(AppInstance.m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(AppInstance.m_renderer);

    /**************** BEGIN  *****************/

    while (SDL_PollEvent(&m_event)) {
      switch (m_event.type) {
      case SDL_QUIT:
        destroy_application(EXIT_SUCCESS);
        break;
      }
    }

    /**************** END  *****************/

    SDL_RenderPresent(AppInstance.m_renderer);
    SDL_Delay(16);
  }
}

static void create_application() {
  SDL_Window *window;
  SDL_Renderer *renderer;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    // log error
    destroy_application(EXIT_FAILURE);
  }

  window = SDL_CreateWindow(APP_WINDOW_TITLE, SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, APP_WINDOW_WIDTH,
                            APP_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == NULL) {
    // log error
    destroy_application(EXIT_FAILURE);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    // log error
    destroy_application(EXIT_FAILURE);
  }

  AppInstance.m_running = true;
  AppInstance.m_window = window;
  AppInstance.m_renderer = renderer;
}

int main(int argc, char **argv) {
  // init app
  create_application();

  // run app
  run_application();

  // destroy app
  destroy_application(EXIT_SUCCESS);
}

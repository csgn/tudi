#include "app.h"
#include "event.h"
#include "loader.h"
#include "object.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_loadso.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_video.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Application AppInstance;

void destroy_application(bool exit_status) {
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

static void tick(float *deltaTime, uint32_t *prevTime) {
  uint32_t currentTime = SDL_GetTicks();
  *deltaTime =
      (currentTime - *prevTime) / 1000.0f; // Convert milliseconds to seconds
  *prevTime = currentTime;
}

static void run_application() {
  // log info

  load_objects("./game/");

  int i = 0;
  SharedObject *o;
  for (i = 0; (o = AppInstance.m_objects[i]) && o != NULL &&
              i < AppInstance.m_object_count;
       i++) {
    o->cb__onStart(&AppInstance);
  }

  uint32_t prevTime = SDL_GetTicks();
  float deltaTime = 0.0f;

  while (AppInstance.m_running) {
    tick(&deltaTime, &prevTime);
    AppInstance.m_delta = deltaTime;

    char text[128];
    float fps = 1.0f / AppInstance.m_delta;
    printf("FPS: %.1f\r", fps);

    SDL_SetRenderDrawColor(AppInstance.m_renderer, 0, 0, 0, 0);
    SDL_RenderClear(AppInstance.m_renderer);

    // EVENT
    event_loop();

    // UPDATE
    for (i = 0; (o = AppInstance.m_objects[i]) && o != NULL &&
                i < AppInstance.m_object_count;
         i++) {
      o->cb__onUpdate();
    }

    // RENDER
    for (i = 0; (o = AppInstance.m_objects[i]) && o != NULL &&
                i < AppInstance.m_object_count;
         i++) {
      o->cb__onRender();
    }

    /**************** END  *****************/

    SDL_RenderPresent(AppInstance.m_renderer);
    SDL_Delay(16);
  }
}

static void create_application() {
  SDL_Window *window;
  SDL_Renderer *renderer;
  SDL_Event event;

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
  AppInstance.m_event = event;
  AppInstance.m_window = window;
  AppInstance.m_renderer = renderer;
  AppInstance.m_object_count = 0;
  AppInstance.m_objects = (SharedObject **)malloc(sizeof(SharedObject *));
  AppInstance.m_winW = APP_WINDOW_WIDTH;
  AppInstance.m_winH = APP_WINDOW_HEIGHT;
  memset(AppInstance.m_objects, 0, sizeof(SharedObject **));
}

int main(int argc, char **argv) {
  // init app
  create_application();

  // run app
  run_application();

  // destroy app
  destroy_application(EXIT_SUCCESS);
}

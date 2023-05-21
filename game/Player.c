#include "../tudi/src/core/app.h"

#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_scancode.h>

#include <dlfcn.h>
#include <stdio.h>

typedef struct {
  SDL_Rect rect;
  SDL_Color color;
  int velocity;
} Player;

static Application *_app;
static Player p;

void onStart(Application *app) {
  _app = app;

  Player _p = {.rect = {.w = 32, .h = 32, .x = 0, .y = 0},
               .color = {.r = 255, .g = 255, .b = 255, .a = 255},
               .velocity = 8};

  p = _p;
}

void onUpdate() {
  if (_app->m_keys[SDL_SCANCODE_W]) {
    p.rect.y += -8;
  }
  if (_app->m_keys[SDL_SCANCODE_A]) {
    p.rect.x += -8;
  }

  if (_app->m_keys[SDL_SCANCODE_S]) {
    p.rect.y += 8;
  }

  if (_app->m_keys[SDL_SCANCODE_D]) {
    p.rect.x += 8;
  }
}

void onRender() {
  SDL_SetRenderDrawColor(_app->m_renderer, p.color.r, p.color.g, p.color.b,
                         p.color.a);
  SDL_RenderFillRect(_app->m_renderer, &(p.rect));
}

void onDestroy() {}

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
  float velocity;
} Player;

static Application *_app;
static Player p;

static void movement() {
  static bool isWKeyPressed = false;
  static bool isSKeyPressed = false;
  static bool isAKeyPressed = false;
  static bool isDKeyPressed = false;

  if (_app->m_keys[SDL_SCANCODE_W]) {
    if (!isWKeyPressed) {
      isWKeyPressed = true;
      if (p.rect.y > 0) {
        p.rect.y += -p.velocity * _app->m_delta;
      }
    }
  } else {
    isWKeyPressed = false;
  }

  if (_app->m_keys[SDL_SCANCODE_S]) {
    if (!isSKeyPressed) {
      isSKeyPressed = true;
      if (p.rect.y < _app->m_winH - p.rect.h) {
        p.rect.y += p.velocity * _app->m_delta;
      }
    }
  } else {
    isSKeyPressed = false;
  }

  if (_app->m_keys[SDL_SCANCODE_A]) {
    if (!isAKeyPressed) {
      isAKeyPressed = true;
      if (p.rect.x > 0) {
        p.rect.x += -p.velocity * _app->m_delta;
      }
    }
  } else {
    isAKeyPressed = false;
  }

  if (_app->m_keys[SDL_SCANCODE_D]) {
    if (!isDKeyPressed) {
      isDKeyPressed = true;
      if (p.rect.x < _app->m_winW - p.rect.w) {
        p.rect.x += p.velocity * _app->m_delta;
      }
    }
  } else {
    isDKeyPressed = false;
  }
}

void onStart(Application *app) {
  _app = app;

  Player _p = {.rect = {.w = 32, .h = 32, .x = 0, .y = 0},
               .color = {.r = 255, .g = 255, .b = 255, .a = 255},
               .velocity = 1000.0f};

  p = _p;
}

void onUpdate() { movement(); }

void onRender() {
  SDL_SetRenderDrawColor(_app->m_renderer, p.color.r, p.color.g, p.color.b,
                         p.color.a);
  SDL_RenderFillRect(_app->m_renderer, &(p.rect));
}

void onDestroy() {}

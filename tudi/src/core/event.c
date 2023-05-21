#include "event.h"
#include "app.h"
#include <SDL2/SDL_events.h>

static void keydown(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < 350) {
    AppInstance.m_keys[event->keysym.scancode] = 1;
  }
}

static void keyup(SDL_KeyboardEvent *event) {
  if (event->repeat == 0 && event->keysym.scancode < 350) {
    AppInstance.m_keys[event->keysym.scancode] = 0;
  }
}

static void mousedown(SDL_MouseButtonEvent *event) {}
static void mouseup(SDL_MouseButtonEvent *event) {}
static void mousemotion(SDL_MouseMotionEvent *event) {}

void event_loop() {
  while (SDL_PollEvent(&AppInstance.m_event)) {
    switch (AppInstance.m_event.type) {
    case SDL_QUIT:
      destroy_application(EXIT_SUCCESS);
      break;
    case SDL_KEYDOWN:
      keydown(&(AppInstance.m_event).key);
      break;
    case SDL_KEYUP:
      keyup(&(AppInstance.m_event).key);
      break;
    case SDL_MOUSEBUTTONDOWN:
      mousedown(&(AppInstance.m_event).button);
      break;
    case SDL_MOUSEBUTTONUP:
      mouseup(&(AppInstance.m_event).button);
      break;
    case SDL_MOUSEMOTION:
      mousemotion(&(AppInstance.m_event).motion);
      break;
    }
  }
}

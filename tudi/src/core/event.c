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
    }
  }
}

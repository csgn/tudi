#ifndef __APP_H__
#define __APP_H__

#include "object.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>

#include <stdbool.h>
#include <sys/types.h>

#define APP_WINDOW_TITLE "tudi@0.0.0"
#define APP_WINDOW_WIDTH 800
#define APP_WINDOW_HEIGHT 600

typedef struct {
  bool m_running;
  SDL_Renderer *m_renderer;
  SDL_Window *m_window;
  SDL_Event m_event;
  SharedObject **m_objects;
  uint m_object_count;
  uint m_keys[350];
} Application;

void destroy_application(bool);
int main(int argc, char **argv);

extern Application AppInstance;

#endif // __APP_H__

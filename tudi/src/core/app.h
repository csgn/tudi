#ifndef __APP_H__
#define __APP_H__

#include <SDL2/SDL.h>
#include <stdbool.h>

#define APP_WINDOW_TITLE "tudi@0.0.0"
#define APP_WINDOW_WIDTH 800
#define APP_WINDOW_HEIGHT 600

typedef struct {
  bool m_running;
  SDL_Renderer *m_renderer;
  SDL_Window *m_window;
} Application;

static void destroy_application(bool);
static void run_application(void);
static void create_application(void);
int main(int argc, char **argv);

extern Application AppInstance;

#endif // __APP_H__

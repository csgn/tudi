#include "loader.h"
#include "app.h"
#include "object.h"
#include <SDL2/SDL_loadso.h>
#include <dirent.h>
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

DIR *open_dir(const char *_target) {
  DIR *d = opendir(_target);

  if (d == NULL) {
    perror("Failed to open directory");
    return NULL;
  }

  return d;
}

char **read_dir(DIR *d) {
  struct dirent *e;
  int i = 0;
  char **files = (char **)calloc(256, sizeof(char *));
  memset(files, 0, sizeof(char **));

  while ((e = readdir(d)) != NULL) {
    if (e->d_type == DT_REG) {
      if (strstr(e->d_name, ".so") != NULL) {
        files[i++] = e->d_name;
      }
    }
  }

  if (i == 0) {
    free(files);
  }

  return files;
}

void *load_object(const char *_target) {
  void *object = SDL_LoadObject(_target);

  printf("[WILL_LOAD] %s\n", _target);
  if (object == NULL) {
    printf("[LOAD_FAILED] %s\n", SDL_GetError());
    return NULL;
  } else {
    printf("[LOADED] %s(%p)\n", _target, object);
    // void (*start)() = (void (*)())SDL_LoadFunction(object, "onStart");
    // void (*update)() = (void (*)())SDL_LoadFunction(object, "onUpdate");
    // void (*render)() = (void (*)())SDL_LoadFunction(object, "onRender");
    // void (*destroy)() = (void (*)())SDL_LoadFunction(object, "onDestroy");

    // SDL_UnloadObject(object);
  }

  return object;
}

void push_object(char *name, char *fullpath, void *object) {
  SharedObject *new_shared_object = malloc(sizeof(SharedObject));

  if (new_shared_object == NULL) {
    // log error
    return;
  }

  new_shared_object->name = name;
  new_shared_object->fulpath = fullpath;
  new_shared_object->object = object;
  new_shared_object->cb__onStart =
      (void (*)())SDL_LoadFunction(new_shared_object->object, "onStart");
  new_shared_object->cb__onUpdate =
      (void (*)())SDL_LoadFunction(new_shared_object->object, "onUpdate");
  new_shared_object->cb__onRender =
      (void (*)())SDL_LoadFunction(new_shared_object->object, "onRender");
  new_shared_object->cb__onDestroy =
      (void (*)())SDL_LoadFunction(new_shared_object->object, "onDestroy");

  printf("[PUSHING] %s %s %p\n", new_shared_object->name,
         new_shared_object->fulpath, new_shared_object->object);

  AppInstance.m_objects[AppInstance.m_object_count] = new_shared_object;
  AppInstance.m_object_count++;
}

void load_objects(const char *_target) {
  DIR *d = opendir(_target);
  char **files = read_dir(d);

  char *ch;
  int i = 0;
  char *m;
  void *o;
  while ((ch = files[i++]) != NULL) {
    m = malloc(sizeof(char));
    memset(m, 0, sizeof(char));
    strcat(m, _target);
    strcat(m, ch);
    o = load_object(m);
    push_object(ch, m, o);
  }
}

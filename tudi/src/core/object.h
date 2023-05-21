#ifndef __OBJECT_H__
#define __OBJECT_H__

typedef struct {
  char *name;
  char *fulpath;
  void *object;
  void (*cb__onStart)(void *);
  void (*cb__onUpdate)();
  void (*cb__onRender)();
  void (*cb__onDestroy)();
} SharedObject;

#endif // __OBJECT_H__

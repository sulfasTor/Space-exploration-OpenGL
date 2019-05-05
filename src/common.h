#ifndef __COMMON_H__
#define __COMMON_H__

#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>

/* Global variables */

typedef struct {
  GLfloat x, y, z;
  GLfloat theta;
} cam_t;

extern GLuint _pId;
extern GLuint _sphere;
extern cam_t _cam;

#endif /* __COMMON_H__ */

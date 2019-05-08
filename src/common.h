#ifndef __COMMON_H__
#define __COMMON_H__

#include <GL4D/gl4dg.h>
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>
#include <float.h>

/* Global variables */

typedef struct {
  GLfloat x, y, z;
} vector_t;


extern int _wW, _wH;
extern int _xm, _ym;
extern GLuint _pId;
extern GLuint _sphere;
extern GLuint _cube;
extern GLuint _plane;
extern GLuint _torus;
extern vector_t _cam;
extern vector_t _look_at;
extern vector_t _up;
extern vector_t _right;
extern GLfloat _pitch;
extern GLfloat _yaw;
extern GLfloat _roll;


#endif /* __COMMON_H__ */

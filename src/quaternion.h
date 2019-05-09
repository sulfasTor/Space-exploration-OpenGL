#ifndef __QUATERNION_H__
#define __QUATERNION_H__

#include "common.h"

typedef struct
{
  GLfloat x, y, z, w;
} quaternion_t;


quaternion_t get_quaternion_from_axis (vector_t, GLfloat);
quaternion_t get_quaternion_from_euler_angles (GLfloat, GLfloat, GLfloat);
double length (quaternion_t);
void normalize_quaternion(quaternion_t*);
void conjugate (quaternion_t *);
quaternion_t mult (quaternion_t, quaternion_t);
#endif

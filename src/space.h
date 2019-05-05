#ifndef __SPACE_H__
#define __SPACE_H__
#include "window.h"

typedef struct {
  GLuint radius;
  GLuint x, y;
  GLuint tex_id;

} t_star;

t_star generate_star (t_star*,GLuint);

#endif

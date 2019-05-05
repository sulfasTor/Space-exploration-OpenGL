#ifndef __SPACE_H__
#define __SPACE_H__

#include "common.h"

typedef struct {
  GLuint radius;
  GLuint x, y;
  GLuint tex_id;

} t_star;

extern GLuint _space_radius;
extern GLuint _space_tex_id;

//t_star generate_star (t_star*, GLuint);
void generate_space ();
void draw_space ();

#endif

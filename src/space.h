#ifndef __SPACE_H__
#define __SPACE_H__

#include "common.h"
#include <time.h>

typedef struct {
  GLuint radius;
  GLuint x, y, z;

} t_star;

typedef struct {
  GLuint radius;
  GLuint x, y, z;
  GLfloat health;

} t_ovni;

extern const GLuint _space_radius;
extern GLuint _star_tex_id;
extern GLuint _ovni_tex_id;
extern GLuint _space_tex_id;
extern const int _stars_number;
extern const int _ovnis_number;

t_star *_stars;
t_ovni *_ovnis;

void generate_space ();
void draw_space ();
void clean_space ();

#endif

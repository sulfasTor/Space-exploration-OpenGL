#ifndef __SPACE_H__
#define __SPACE_H__

#include "common.h"
#include <time.h>

typedef struct {
  GLuint radius;
  GLfloat x, y, z;

} t_star;

typedef struct {
  GLuint radius;
  GLfloat x, y, z;
  GLfloat speed;
  GLfloat health;

} t_ovni;

extern const GLint _space_radius;
extern GLuint _star_tex_id;
extern GLuint _ovni_tex_id;
extern GLuint _space_tex_id;
extern const int _stars_number;
extern const int _ovnis_number;
extern const vector_t _stars_position;
extern const vector_t _planets_position[2];

t_star *_stars;
t_ovni *_ovnis;

void generate_space ();
void draw_space ();
void clean_space ();

#endif

#ifndef __VESSEL_H__
#define __VESSEL_H__

#include "common.h"
#include "utils.h"

extern GLuint _vessel_vao_id;
extern GLuint _vessel_vbo_id;
extern GLuint _vessel_tex_id;

typedef struct {
  vector_t rot_axis;
  vector_t pos;
  vector_t origin;
  GLfloat speed;
  GLfloat health;
} enemy_t;

void generate_vessels ();
void draw_vessels ();
void clean_vessel ();

#endif

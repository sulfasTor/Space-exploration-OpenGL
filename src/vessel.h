#ifndef __VESSEL_H__
#define __VESSEL_H__

#include "common.h"

extern GLuint _vessel_vao_id;
extern GLuint _vessel_vbo_id;
extern GLuint _vessel_tex_id;

enum e_point_of_view
  {
   INSIDE = 0,
   EXTERIOR,
   COCKPIT
  };

void generate_vessel ();
void draw_vessel ();
void clean_vessel ();
void draw_enemy_vessel ();

#endif

#ifndef __VESSEL_H__
#define __VESSEL_H__

#include "common.h"

extern GLuint _vessel_vao_id;
extern GLuint _vessel_vbo_id;
extern GLuint _vessel_tex_id;

void generate_vessel ();
void draw_vessel (cam_t);

#endif

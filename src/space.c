#include "space.h"

GLuint _space_radius = 100;
GLuint _space_tex_id = 10;

/* t_star generate_star (t_star *stars, GLuint space_rad) */
/* { */
  
/* } */

void generate_space ()
{
  glGenTextures (1, &_space_tex_id);
  glBindTexture (GL_TEXTURE_2D, _space_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
}

void draw_space ()
{
  gl4duBindMatrix("modelMatrix");
  gl4duPushMatrix(); {
    gl4duTranslatef(0.0, 0.0, -810.0);
    gl4duScalef(_space_radius, _space_radius, _space_radius);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _space_tex_id);
  gl4dgDraw(_sphere);
  gl4duBindMatrix(0);
}

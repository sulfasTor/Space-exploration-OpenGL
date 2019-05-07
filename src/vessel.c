#include "vessel.h"

GLfloat _vessel_data[] =
  {
   0.0f, 0.0f, -1.0f,
   -0.6f, 0.0f, 0.0f,
   0.6f,  0.0f, 0.0f,
  };

GLuint _vessel_vao_id = 0;
GLuint _vessel_vbo_id = 0;
GLuint _vessel_tex_id = 0;
GLuint _space_radius;

void generate_vessel ()
{
  GLuint vessel_tex[] = {(255 << 16) + 255};
  
  glGenVertexArrays(1, &_vessel_vao_id);
  glBindVertexArray(_vessel_vao_id);
  glEnableVertexAttribArray(0);
  glGenBuffers(1, &_vessel_vbo_id);
  glBindBuffer(GL_ARRAY_BUFFER, _vessel_vbo_id);
  glBufferData(GL_ARRAY_BUFFER, sizeof (_vessel_data), _vessel_data, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (const void *)0);  
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  
  glGenTextures (1, &_vessel_tex_id);
  glBindTexture (GL_TEXTURE_2D, _vessel_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, vessel_tex);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_vessel ()
{
  gl4duBindMatrix("modelMatrix");
  gl4duPushMatrix(); {
    gl4duRotatef(-90, 0, 1, 0);
    gl4duScalef(1000, 1000, 1000);
    gl4duTranslatef(_cam.x,-_cam.y,_cam.z);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, _vessel_tex_id);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindVertexArray(_vessel_vao_id);
  glDrawArrays(GL_TRIANGLES, 0, 4);
  glBindVertexArray(0);
  gl4duBindMatrix(0);
}

void clean_vessel ()
{
  if(_vessel_vao_id)
    glDeleteVertexArrays(1, &_vessel_vao_id);
  if(_vessel_vbo_id)
    glDeleteBuffers(1, &_vessel_vbo_id);
  if(_vessel_tex_id)
    glDeleteTextures(1, &_vessel_tex_id);
}

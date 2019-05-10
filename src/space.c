#include "space.h"

const GLint _space_radius = 70000;
const GLint _planet_radius = 3000;
const int _stars_number = 1000;
const int _ovnis_number = 500;
const vector_t _planets_position[2] = {{0, 0, 0}, {_planet_radius, -20.0 * _planet_radius, 0}};
const vector_t _stars_position = {0,_space_radius, _space_radius};
GLuint _star_tex_id = 0;
GLuint _ovni_tex_id = 0;
GLuint _planet_tex_id = 0;
GLuint _sun_tex_id = 0;

static GLfloat angle = 0.0;
/* static Gluint _star_vao_id = 0.0; */
/* static Gluint *_star_vbo_id = 0.0; */

t_star generate_star ()
{
  vector_t v = random_vector (2.0 * _planet_radius - 30.0);
  return (t_star) { uniform0to1Random() * 30.0, v.x, v.y, v.z };
}

t_ovni generate_ovni ()
{
  vector_t v = random_vector ( _planet_radius/2.0);
  return (t_ovni) { uniform0to1Random() * 50.0, v.x, 2.0 * _planet_radius, v.z, uniform0to1Random() * 50.0 + 1.0, 100.0 };
}

void generate_space ()
{
  int i;
  GLuint star_tex[] = {RGB (255, 255, 255)};
  GLuint ovni_tex[] = {RGB (255, 255, 0)};
  GLuint planet_tex[] = {100000, RGB (11, 11, 11), RGB (11, 11, 11), RGB (11, 11, 11), 0, 0, RGB (11, 11, 11), 0, RGB (11, 11, 11), 0, RGB (11, 11, 11), 0, 0, 0, RGB (255, 255, 255)};
  GLuint sun_tex[15];

  for (i = 0; i < 15; ++i)
    sun_tex[i] = RGB (255, rand()%255, 0);
  
  _stars = (t_star*) malloc (_stars_number * sizeof (t_star));
  _ovnis = (t_ovni*) malloc (_ovnis_number * sizeof (t_ovni));

  glGenTextures (1, &_star_tex_id);
  glBindTexture (GL_TEXTURE_2D, _star_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, star_tex);
  glBindTexture (GL_TEXTURE_2D, 0);
  
  glGenTextures (1, &_ovni_tex_id);
  glBindTexture (GL_TEXTURE_2D, _ovni_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, ovni_tex);
  glBindTexture (GL_TEXTURE_2D, 0);
  
  glGenTextures (1, &_planet_tex_id);
  glBindTexture (GL_TEXTURE_2D, _planet_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 15, 0, GL_RGBA, GL_UNSIGNED_BYTE, planet_tex);
  glBindTexture (GL_TEXTURE_2D, 0);

  glGenTextures (1, &_sun_tex_id);
  glBindTexture (GL_TEXTURE_2D, _sun_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 15, 0, GL_RGBA, GL_UNSIGNED_BYTE, sun_tex);
  glBindTexture (GL_TEXTURE_2D, 0);

  
  for (i = 0; i < _stars_number; ++i)
      _stars[i] = generate_star ();

  for (i = 0; i < _ovnis_number; ++i)
    _ovnis[i] = generate_ovni ();

}

void draw_space ()
{
  int i;

  gl4duBindMatrix("modelMatrix"); /* Do not remove */

  /* SUN */
  
  gl4duPushMatrix(); {
    gl4duTranslatef(_stars_position.x, _stars_position.y, _stars_position.z+_space_radius);
    gl4duScalef(_space_radius, _space_radius, _space_radius);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _sun_tex_id);
  gl4dgDraw(_sphere);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  /* Main planet */
  
  gl4duPushMatrix(); {
    gl4duTranslatef(0, 0, 0);
    gl4duScalef(_planet_radius * 2.0, _planet_radius * 2.0, _planet_radius * 2.0);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glDisable(GL_CULL_FACE);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _planet_tex_id);
  gl4dgDraw(_sphere);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Second planet */
  
  gl4duPushMatrix(); {
    gl4duTranslatef(-_planets_position[1].x, -_planets_position[1].y, -_planets_position[1].z);
    gl4duScalef(_planet_radius * 2.0, _planet_radius * 2.0, _planet_radius * 2.0);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glDisable(GL_CULL_FACE);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _planet_tex_id);
  gl4dgDraw(_sphere);
  glBindTexture(GL_TEXTURE_2D, 0);


  /* Moon */
  angle += 1.0;
  gl4duPushMatrix(); {
    gl4duRotatef(angle, 1, 0, 0);
    gl4duTranslatef(0.0, 0.0, 3.0*_planet_radius);
    gl4duScalef(_planet_radius * 0.5, _planet_radius * 0.5, _planet_radius * 0.5);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glEnable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _star_tex_id);
  gl4dgDraw(_sphere);
  glBindTexture(GL_TEXTURE_2D, 0);


  for (i = 0; i < _stars_number; ++i)
    {
      gl4duPushMatrix(); {
  	gl4duTranslatef(_stars[i].x, _stars[i].y, _stars[i].z);
  	gl4duScalef(_stars[i].radius, _stars[i].radius, _stars[i].radius);
  	gl4duSendMatrices();
      } gl4duPopMatrix();
      glEnable(GL_CULL_FACE);
      glDisable(GL_DEPTH_TEST);
      glActiveTexture(GL_TEXTURE0);
      glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
      glBindTexture(GL_TEXTURE_2D, _star_tex_id);
      gl4dgDraw(_sphere);
      glBindTexture(GL_TEXTURE_2D, 0);
    }

    for (i = 0; i < _ovnis_number; ++i)
    {
      _ovnis[i].y -= _ovnis[i].speed;
      if (_ovnis[i].y <= -2.0 * _planet_radius)
	_ovnis[i].y = 2.0 * _planet_radius;
      gl4duPushMatrix(); {
    	gl4duTranslatef(_ovnis[i].x, _ovnis[i].y, _ovnis[i].z);
    	gl4duScalef(_ovnis[i].radius, _ovnis[i].radius, _ovnis[i].radius);
    	gl4duSendMatrices();
      } gl4duPopMatrix();
      glEnable(GL_CULL_FACE);
      glDisable(GL_DEPTH_TEST);
      glActiveTexture(GL_TEXTURE0);
      glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
      glBindTexture(GL_TEXTURE_2D, _ovni_tex_id);
      gl4dgDraw(_cube);
      glBindTexture(GL_TEXTURE_2D, 0);
    }
  
    gl4duBindMatrix(0); /* Finish pushing matrices */
}

void clean_space ()
{
  if (_stars)
    free (_stars);
  if (_ovnis)
    free (_ovnis);
  if (_star_tex_id)
    glDeleteTextures (1, &_star_tex_id);
  if (_ovni_tex_id)
    glDeleteTextures (1, &_ovni_tex_id);
}

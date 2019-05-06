#include "space.h"

const GLuint _space_radius = 3000;
GLuint _star_tex_id = 0;
GLuint _ovni_tex_id = 0;
GLuint _space_tex_id = 0;
const int _stars_number = 800;
const int _ovnis_number = 200;

double uniform0to1Random() {
    double r = random();
    return r / ((double)RAND_MAX + 1);
}

t_star generate_star ()
{
  return (t_star) {
    rand () % 10,
      _space_radius * uniform0to1Random() - _space_radius + _space_radius / 2.0f,
      _space_radius * uniform0to1Random() - _space_radius + _space_radius / 2.0f,
      _space_radius * uniform0to1Random() - _space_radius + _space_radius / 2.0f,
      };
}

t_ovni generate_ovni ()
{
  return (t_ovni) {
    rand () % 50,
      _space_radius * uniform0to1Random() - _space_radius + _space_radius / 2.0f,
      _space_radius * uniform0to1Random() - _space_radius + _space_radius / 2.0f,
      _space_radius * uniform0to1Random() - _space_radius + _space_radius / 2.0f,
      100.0
      };
}

void generate_space ()
{
  int i;
  GLuint star_tex[] = {(255 << 8) + 255};
  GLuint ovni_tex[] = {255};
  SDL_Surface * s;
  
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
  
  glGenTextures (1, &_space_tex_id);
  glBindTexture (GL_TEXTURE_2D, _space_tex_id);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  if ((s = SDL_LoadBMP("images/universe.bmp")))
    {
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0,
		   s->format->BytesPerPixel == 3 ? GL_BGR : GL_BGRA, GL_UNSIGNED_BYTE, s->pixels);
      SDL_FreeSurface(s);
    }
  else
    glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);
  glBindTexture (GL_TEXTURE_2D, 0);
  
  for (i = 0; i < _stars_number; ++i)
      _stars[i] = generate_star ();

  for (i = 0; i < _ovnis_number; ++i)
    _ovnis[i] = generate_ovni ();

}

void draw_space ()
{
  int i;
  gl4duBindMatrix("modelMatrix");
  gl4duPushMatrix(); {
    gl4duTranslatef(_space_radius / 2.0f, _space_radius / 2.0f, _space_radius / 2.0f);
    gl4duScalef(_space_radius / 3,  _space_radius / 3, _space_radius / 3);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  //glDisable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _space_tex_id);
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
      gl4duPushMatrix(); {
	gl4duRotatef(-45, 0, 1, 0);
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

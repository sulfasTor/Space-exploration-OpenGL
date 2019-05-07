#include "space.h"
#define NSUM 25

const GLint _space_radius = 3000;
GLuint _star_tex_id = 0;
GLuint _ovni_tex_id = 0;
GLuint _space_tex_id = 0;
const int _stars_number = 1000;
const int _ovnis_number = 500;

double uniform0to1Random() {
  double r = random();
  return r / ((double)RAND_MAX + 1);
}

/* method described by Abramowitz and Stegun from http://c-faq.com/lib/gaussian.html */
double gaussrand()
{
  static double U, V;
  static int phase = 0;
  double Z;

  if (phase == 0) {
    U = (rand() + 1.) / (RAND_MAX + 2.);
    V = rand() / (RAND_MAX + 1.);
    Z = sqrt(-2 * log(U)) * sin(2 * M_PI * V);
  } else
    Z = sqrt(-2 * log(U)) * cos(2 * M_PI * V);

  phase = 1 - phase;
  
  return Z;
}

vector_t random_vector(GLfloat r)
{
  GLfloat x, y, z;
  GLfloat theta = gaussrand () * 360;
  GLfloat phi = gaussrand () * 360;
  
  x = r * cos(theta) * sin(phi);
  y = r * sin(theta) * sin(phi);
  z = r * cos(phi);
    
  return (vector_t) {x, y, z};
}

t_star generate_star ()
{
  vector_t v = random_vector (2.0 * _space_radius - 30.0);
  return (t_star) { uniform0to1Random() * 30.0, v.x, v.y, v.z };
}

t_ovni generate_ovni ()
{
  vector_t v = random_vector ( _space_radius/2.0);
  printf ("vec: %f, %f, %f\n", v.x, v.y, v.z);
  return (t_ovni) { uniform0to1Random() * 50.0, v.x, 2.0 * _space_radius, v.z, uniform0to1Random() * 50.0 + 1.0, 100.0 };
}

void generate_space ()
{
  int i;
  GLuint star_tex[] = {RGB (255, 255, 255)};
  GLuint ovni_tex[] = {RGB (255, 255, 0)};
  GLuint space_tex[] = {100000, RGB (11, 11, 11), RGB (11, 11, 11), RGB (11, 11, 11), 0, 0, RGB (11, 11, 11), 0, RGB (11, 11, 11), 0, RGB (11, 11, 11), 0, 0, 0, RGB (255, 255, 255)};
  //SDL_Surface * s;
  
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
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameterf (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
  /* if ((s = SDL_LoadBMP("images/universe-2.bmp"))) */
  /*   { */
  /*     glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, s->w, s->h, 0, */
  /* 		   s->format->BytesPerPixel == 3 ? GL_BGR : GL_BGRA, GL_UNSIGNED_BYTE, s->pixels); */
  /*     SDL_FreeSurface(s); */
  /*   } */
  /* else */
  glTexImage2D (GL_TEXTURE_2D, 0, GL_RGBA, 1, 15, 0, GL_RGBA, GL_UNSIGNED_BYTE, space_tex);
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
    gl4duTranslatef(0, 0, 0);
    gl4duScalef(100, 10, 10);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glDisable(GL_CULL_FACE);
  glActiveTexture(GL_TEXTURE0);
  glUniform1i(glGetUniformLocation(_pId, "tex"), 0);
  glBindTexture(GL_TEXTURE_2D, _star_tex_id);
  gl4dgDraw(_torus);
  glBindTexture(GL_TEXTURE_2D, 0);

  gl4duPushMatrix(); {
    gl4duTranslatef(0, 0, 0);
    gl4duScalef(_space_radius * 2.0, _space_radius * 2.0, _space_radius * 2.0);
    gl4duSendMatrices();
  } gl4duPopMatrix();
  glDisable(GL_CULL_FACE);
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
      _ovnis[i].y -= _ovnis[i].speed;
      if (_ovnis[i].y <= -2.0 * _space_radius)
	_ovnis[i].y = 2.0 * _space_radius;
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

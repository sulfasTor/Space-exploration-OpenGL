/*!\file window.h
 *
 * \brief Exploration intergalactique
 *
 * \author Moises TORRES AGUILAR, torresmoisesa@gmail.com
 * \date May 4 2019
 */

#include "common.h"
#include "space.h"
#include "vessel.h"

enum e_keys {
	     KLEFT = 0,
 	     KRIGHT,
	     KUP,
	     KDOWN,
	     KWARP
};

static GLuint _keys[] = {0, 0, 0, 0, 0};
int _wW = 1000, _wH = 800;
int _xm = 500, _ym = 500;
static int _xm_last = 500, _ym_last = 500;

GLuint _pId = 0;
GLuint _sphere = 0;
GLuint _plane = 0;
GLuint _torus = 0;
GLuint _cube = 0;
vector_t _cam = {0, 0, -4000};

GLfloat _pitch = 0.0;
GLfloat _yaw = 0.0;
GLfloat _roll = 0.0;
static GLfloat _msensitivity = 0.00005;
static GLfloat _bound = 70000;

vector_t _look_at = {0, 0, 1};
vector_t _up = {0, 1, 0};
vector_t _right = {1, 0, 0};

/* Forward declarations */

void quit(void);
void init(void);
void init_data(void);
void resize(int, int);
void draw(void);
void keyup(int);
void keydown(int);
void pmotion(int, int);
void idle(void);
void normalize (vector_t *);
void pitch_and_yaw();
void roll (GLfloat);
vector_t cross_product(vector_t, vector_t);

/*!\brief créé la fenêtre, un screen 2D effacé en noir et lance une
 *  boucle infinie.*/
int main (int argc, char ** argv)
{
  if(!gl4duwCreateWindow(argc, argv, "Exploration intergalactique", 10, 10,
                         _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;

  init ();
  init_data ();
  atexit (quit);
  gl4duwResizeFunc (resize);
  gl4duwKeyUpFunc(keyup);
  gl4duwKeyDownFunc (keydown);
  gl4duwPassiveMotionFunc (pmotion);
  gl4duwDisplayFunc (draw);
  gl4duwIdleFunc (idle);
  gl4duwMainLoop ();
  return 0;
}

/*!\brief initialise les paramètres OpenGL et les données */
void init (void)
{
  glClearColor(0, 0, 0.0, 0);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  _pId  = gl4duCreateProgram ("<vs>shaders/vertex.vs", "<fs>shaders/fragment.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelMatrix");
  gl4duGenMatrix(GL_FLOAT, "viewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  resize(_wW, _wH);
}

void init_data ()
{
  _sphere = gl4dgGenSpheref (30, 30);
  _cube = gl4dgGenCubef();
  _plane = gl4dgGenQuadf ();
  _torus = gl4dgGenTorusf(30, 30, 1);

  srand (time (0)); 
  generate_space ();
  generate_vessel ();
  glBindTexture(GL_TEXTURE_2D, 0);
}

/*!\brief Cette fonction paramétre la vue (viewport) OpenGL en
 * fonction des dimensions de la fenêtre.*/
void resize (int w, int h)
{
  _wW  = w; _wH = h;
  glViewport (0, 0, _wW, _wH);
  gl4duBindMatrix ("projectionMatrix");
  gl4duLoadIdentityf ();
  gl4duFrustumf(-1.0, 1.0, -1.0 * _wH / (float) _wW, 1.0 * _wH / (float)_wW, 1.0, 2.0f * _space_radius * _space_radius + 1.0);
}

void quit (void)
{
  clean_space ();
  clean_vessel ();
  gl4duClean(GL4DU_ALL);
}

void draw (void)
{
  //printf ("P: %f %f %f\n", _cam.x, _cam.y, _cam.z);
  /* printf ("F %f %f %f\n", _look_at.x, _look_at.y, _look_at.z); */
  printf ("U %f %f %f\n", _up.x, _up.y, _up.z);
  /* printf ("R %f %f %f\n", _right.x, _right.y, _right.z); */
  /* printf ("##############################################\n"); */
  
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(_pId);
  gl4duBindMatrix("viewMatrix");
  gl4duLoadIdentityf();
  gl4duLookAtf (_cam.x, _cam.y, _cam.z, _look_at.x + _cam.x, _look_at.y + _cam.y, _look_at.z + _cam.z, _up.x, _up.y, _up.z);
  
  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();
  gl4duBindMatrix(0);
  draw_space ();
  draw_vessel ();
}

void normalize (vector_t *v)
{
  GLfloat norm;

  norm = v->x * v->x + v->y * v->y + v->z * v->z;
  norm = sqrt (norm);

  v->x /= norm;
  v->y /= norm;
  v->z /= norm;
}

void pmotion(int x, int y)
{
  _xm = x;
  _ym = y;
}

void keydown(int keycode) {
  GLint v[2];
  switch(keycode) {
  case 'q':
    _keys[KLEFT] = 1;
    break;
  case 'd':
    _keys[KRIGHT] = 1;
    break;
  case 'z':
    _keys[KUP] = 1;
    break;
  case 's':
    _keys[KDOWN] = 1;
    break;
  case 'h':
    _keys[KWARP] = 1;
    break;
  case GL4DK_ESCAPE:
  case 'x':
    exit(0);
    /* when 'w' pressed, toggle between line and filled mode */
  case 'w':
    glGetIntegerv(GL_POLYGON_MODE, v);
    if(v[0] == GL_FILL) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      glLineWidth(3.0);
    } else {
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      glLineWidth(1.0);
    }
    break;
  default:
    break;
  }
}

void keyup(int keycode) {
  switch(keycode) {
  case 'q':
    _keys[KLEFT] = 0;
    break;
  case 'd':
    _keys[KRIGHT] = 0;
    break;
  case 'z':
    _keys[KUP] = 0;
    break;
  case 's':
    _keys[KDOWN] = 0;
    break;
  case 'h':
    _keys[KWARP] = 0;
    break;
  default:
    break;
  }
}

void idle(void) {
  GLboolean modified = 0;
  static GLfloat speed = 1.0;
  double dt, dtheta = M_PI;
  static double t0 = 0, t;
  dt = ((t = gl4dGetElapsedTime()) - t0) / 1000.0;
  t0 = t;

  printf ("#########idle\n");
  if(_keys[KWARP])
    {
      speed = 1000.0;
      gl4duBindMatrix ("projectionMatrix");
      gl4duLoadIdentityf ();
      gl4duFrustumf(-5.5, 5.0, -5.0 * _wH / (float) _wW, 5.0 * _wH / (float)_wW, 1.0, 2.0f * _space_radius * _space_radius + 1);
      gl4duBindMatrix (0);
      modified = 1;
    }
  else
    resize(_wW, _wH);

  if(_keys[KLEFT])
      roll (dt * dtheta);
  if(_keys[KRIGHT])
      roll (-dt * dtheta);
  if(_keys[KUP])
    {
      //if (speed < 50.0)
      speed += 10.0;
      modified = 1;
    }  
  if(_keys[KDOWN])
    {
      speed += -10.0;
      modified = 1;
    }
  if (!modified)
    speed = 10.0;
  pitch_and_yaw ();
  _cam.x += _look_at.x * speed;
  _cam.y += _look_at.y * speed;
  _cam.z += _look_at.z * speed;
  
  if (fabs(_cam.x) >= _bound || fabs(_cam.x) >= _bound || fabs(_cam.x) >= _bound)
    {
      _cam.x = 0.0;
      _cam.y = 0.0;
      _cam.z = 0.0;
    }
}

vector_t cross_product(vector_t a, vector_t b)
{
  vector_t c = (vector_t)
    {
     a.y * b.z - a.z * b.y,
     a.z * b.x - a.x * b.z,
     a.x * b.y - a.y * b.x
    }; 
  return c;
}

void pitch_and_yaw ()
{
  GLfloat x_offset, y_offset;

  x_offset = _xm - _xm_last;
  y_offset = _ym_last - _ym;
  _xm = _xm_last;
  _ym = _ym_last;
    
  x_offset *= _msensitivity;
  y_offset *= _msensitivity;

  _yaw += x_offset;
  _pitch += y_offset;
    
  _look_at.y = sin(_pitch);
  _look_at.z = sin(_yaw) * cos(_pitch);
  _look_at.x = cos(_yaw) * cos(_pitch);
  normalize (&_look_at);
  
  //vector_t up_y = (vector_t) {0.0f,1.0f,0.0f};
  _right = cross_product (_look_at, _up);
  normalize (&_right);
  
  _up = cross_product (_right, _look_at);
  normalize (&_up);
}

void roll (GLfloat angle)
{
  _roll += angle;
  _up.x = cos (_roll);
  _up.y = sin (_roll);
  _up.z = 0;
  normalize (&_up);
  
  _right = cross_product (_look_at, _up);
  normalize (&_right);
}

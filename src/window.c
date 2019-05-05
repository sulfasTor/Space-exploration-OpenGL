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
	     KDOWN
};

static GLuint _keys[] = {0, 0, 0, 0};
static int _wW = 1000, _wH = 800;
static int _xm = 0, _ym = 0;

GLuint _pId = 0;
GLuint _sphere = 0;
cam_t _cam = {0, 0, -100, 0};
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
  glClearColor(1.0f, 0.0f, 1.0f, 0.0f);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  _pId  = gl4duCreateProgram ("<vs>shaders/vertex.vs", "<fs>shaders/fragment.fs", NULL);
  gl4duGenMatrix(GL_FLOAT, "modelMatrix");
  gl4duGenMatrix(GL_FLOAT, "viewMatrix");
  gl4duGenMatrix(GL_FLOAT, "projectionMatrix");
  glViewport (0, 0, _wW, _wH);
  gl4duBindMatrix ("projectionMatrix");
  gl4duLoadIdentityf ();
  gl4duFrustumf (-0.5, 0.5, -0.5 * _wH / _wW, 0.5 * _wH / _wW, 1.0, 10000.0);
  resize(_wW, _wH);
}

void init_data ()
{
  //_sphere = gl4dgGenSpheref (20, 20);
  _sphere = gl4dgGenCubef(); // Debugging
  
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
  gl4duFrustumf (-0.5, 0.5, -0.5 * _wH / _wW, 0.5 * _wH / _wW, 1.0, 10000.0);
}

void quit (void)
{
  gl4duClean(GL4DU_ALL);
}

void draw (void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(_pId);
  gl4duBindMatrix("viewMatrix");
  gl4duLoadIdentityf();
  /* gl4duLookAtf(_cam.x, 3.0, _cam.z,  */
  /* 	       _cam.x - sin(_cam.theta), (_ym - (_wH >> 1)) / (GLfloat)_wH, _cam.z - cos(_cam.theta),  */
  /* 	       0.0, 1.0,0.0); */
  gl4duLookAtf(_cam.x, 3.0, _cam.z,
  	       (_xm - (_wW >> 1)) / (GLfloat)_wW, 3.0 - (_ym - (_wH >> 1)) / (GLfloat)_wH, _cam.z - cos(_cam.theta),
  	       0.0, 1.0,0.0);

  gl4duBindMatrix("modelMatrix");
  gl4duLoadIdentityf();
  gl4duBindMatrix(0);
  draw_space ();
  draw_vessel (_cam);
}

void pmotion(int x, int y)
{
  _xm = x; 
  _ym = y;
}

void keydown(int keycode) {
  GLint v[2];
  switch(keycode) {
  case GL4DK_LEFT:
    _keys[KLEFT] = 1;
    break;
  case GL4DK_RIGHT:
    _keys[KRIGHT] = 1;
    break;
  case GL4DK_UP:
    _keys[KUP] = 1;
    break;
  case GL4DK_DOWN:
    _keys[KDOWN] = 1;
    break;
  case GL4DK_ESCAPE:
  case 'q':
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
  case GL4DK_LEFT:
    _keys[KLEFT] = 0;
    break;
  case GL4DK_RIGHT:
    _keys[KRIGHT] = 0;
    break;
  case GL4DK_UP:
    _keys[KUP] = 0;
    break;
  case GL4DK_DOWN:
    _keys[KDOWN] = 0;
    break;
  default:
    break;
  }
}

void idle(void) {
  double dt, step = 0.5;
  double t0 = 0, t;
  dt = ((t = gl4dGetElapsedTime()) - t0) / 1000.0;
  t0 = t;
  
  /* if(_keys[KLEFT]) */
  /*   _cam.theta += step; */
  /* if(_keys[KRIGHT]) */
  /*   _cam.theta -= step; */
  if(_keys[KUP]) {
    _cam.x += -dt * step * sin(_cam.theta);
    _cam.z += -dt * step * cos(_cam.theta);
  }
  if(_keys[KDOWN]) {
    _cam.x += dt * step * sin(_cam.theta);
    _cam.z += dt * step * cos(_cam.theta);
  }
}

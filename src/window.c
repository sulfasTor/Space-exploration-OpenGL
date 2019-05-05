/*!\file window.h
 *
 * \brief Exploration intergalactique
 *
 * \author Moises TORRES AGUILAR, torresmoisesa@gmail.com
 * \date May 4 2019
 */

#include "window.h"

/*!\brief créé la fenêtre, un screen 2D effacé en noir et lance une
 *  boucle infinie.*/
int main (int argc, char ** argv)
{
  if (!gl4duwCreateWindow (argc, argv, "Exploration intergalactique", 0, 0, 
			   _wW, _wH, GL4DW_RESIZABLE | GL4DW_SHOWN))
    return 1;

  init ();
  atexit (quit);
  gl4duwResizeFunc (resize);
  gl4duwDisplayFunc (draw);
  gl4duwMainLoop ();
  return 0;
}

/*!\brief initialise les paramètres OpenGL et les données */
static void init (void)
{
  glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
  glEnable (GL_CULL_FACE);
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_TEXTURE_2D);
  _pId  = gl4duCreateProgram ("<vs>../shaders/shader.vs", "<fs>../shaders/shader.fs", NULL);
  gl4duGenMatrix (GL_FLOAT, "modelMatrix");
  gl4duGenMatrix (GL_FLOAT, "viewMatrix");
  gl4duGenMatrix (GL_FLOAT, "projectionMatrix");
  resize(_wW, _wH);
}

/*!\brief Cette fonction paramétre la vue (viewport) OpenGL en
 * fonction des dimensions de la fenêtre.*/
static void resize (int w, int h)
{
  _wW  = w; _wH = h;
  glViewport (0, 0, _wW, _wH);
  gl4duBindMatrix ("projectionMatrix");
  gl4duLoadIdentityf ();
  gl4duFrustumf (-0.5, 0.5, -0.5 * _wH / _wW, 0.5 * _wH / _wW, 1.0, 1000.0);
  gl4duBindMatrix ("modelViewMatrix");
}

static void quit (void)
{
  gl4duClean(GL4DU_ALL);
}
static void draw (void)
{
  
}

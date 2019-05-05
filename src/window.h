/*!\file window.h
 *
 * \brief Exploration intergalactique
 *
 * \author Moises TORRES AGUILAR, torresmoisesa@gmail.com
 * \date May 4 2019
 */
#ifndef __WINDOW_H__
#define __WINDOW_H__

#include <GL4D/gl4dg.h>
#include <GL4D/gl4duw_SDL2.h>

#include "space.h"

enum e_keys {
	     KLEFT = 0,
 	     KRIGHT,
	     KUP,
	     KDOWN
};

/*!\brief virtual keyboard for direction commands */
static GLuint _keys[] = {0, 0, 0, 0};

typedef struct cam_t cam_t;
/*!\brief a data structure for storing camera position and
 * orientation */
struct cam_t {
  GLfloat x, z;
  GLfloat theta;
};

/* Global variables */

static int _wW = 800, _wH = 600;
static int _xm = 0, _ym = 0;
static GLuint _pId = 0;
static GLuint _space_radius = 100;
static GLuint _space_tex_id = 0;
static GLuint _sphere = 0;
static cam_t _cam = {0, 0, 0};

static void quit(void);
static void init(void);
static void init_data(void);
static void resize(int, int);
static void draw(void);
static void keyup(int);
static void keydown(int);
static void pmotion(int, int);
static void idle(void);

#endif

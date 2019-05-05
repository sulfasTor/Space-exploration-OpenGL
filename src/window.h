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
#include <GL4D/gl4dp.h>
#include <GL4D/gl4duw_SDL2.h>

/*!\brief opened window width and height */
static int _wW = 800, _wH = 600;
/*!\brief GLSL program Id */
static GLuint _pId = 0;

static void quit(void);
static void init(void);
static void resize(int w, int h);
static void draw(void);

#endif

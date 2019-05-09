#include "utils.h"

double uniform0to1Random() {
  double r = random();
  return r / ((double)RAND_MAX + 1);
}

double uniformMinus1to1Random() {
  double r = random();
  return r / (double)RAND_MAX;
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

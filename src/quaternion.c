#include "quaternion.c"

quaternion_t get_quaternion_from_axis (GLfloat x, GLfloat y, GLfloat z, GLfloat theta)
{
  GLfloat x, y, z, w;
  
  x = A.x * sin (theta / 2);
  y = A.y * sin (theta / 2);
  z = A.z * sin (theta / 2);
  w = cos (theta / 2);

  return (quaternion_t) {x, y, z, w};
}
double length (quaternion_t q)
{
  return sqrt(q.x * q.x + q.y * q.y +
              q.z * q.z + q.w * q.w);
}

void normalize (quaternion_t *q)
{
  const double l = length(q);

  q->x /= l;
  q->y /= l;
  q->z /= l;
  q->w /= l;
}

void conjugate (quaternion_t *q)
{
  q->x *= -1;
  q->y *= -1;
  q->z *= -1;
}

quaternion_t mult (quaternion_t a, quaternion_t b)
{
  GLfloat x, y, z, w;
  
  x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
  y = a.w * b.y - a.x * b.z + a.y * b.w + a.z * b.x;
  z = a.w * b.z + a.x * b.y - a.y * b.x + a.z * b.w;
  w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;

  return (quaternion_t) {x, y, z, w};
}

#include "quaternion.h"

quaternion_t get_quaternion_from_axis (vector_t v, GLfloat theta)
{
  GLfloat xq, yq, zq, w;
  
  xq = v.x * sin (theta / 2);
  yq = v.y * sin (theta / 2);
  zq = v.z * sin (theta / 2);
  w = cos (theta / 2);

  return (quaternion_t) {xq, yq, zq, w};
}

quaternion_t get_quaternion_from_euler_angles (GLfloat pitch, GLfloat yaw, GLfloat roll)
{

  float p = pitch;;
  float y = yaw;
  float r = roll;
  
  float qw = cos(r) * cos(p) * cos(y) + sin(r) * sin(p) * sin(y);
  float qx = sin(r) * cos(p) * cos(y) - cos(r) * sin(p) * sin(y);
  float qy = cos(r) * sin(p) * cos(y) + sin(r) * cos(p) * sin(y);
  float qz = cos(r) * cos(p) * sin(y) - sin(r) * sin(p) * cos(y);

  quaternion_t new_rot = {qx, qy, qz, qw};
  normalize_quaternion (&new_rot);

  return new_rot;
}

double length (quaternion_t q)
{
  return sqrt(q.x * q.x + q.y * q.y +
              q.z * q.z + q.w * q.w);
}

void normalize_quaternion (quaternion_t *q)
{
  const double l = length (*q);

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

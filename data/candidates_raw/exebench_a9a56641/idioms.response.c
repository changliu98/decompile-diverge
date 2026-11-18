void mat4_scale(struct mat4 *dst, struct mat4 *src, struct vec3 *scale)
{
  struct vec3 s = {
    .x = -src->m11 * src->m41 + src->m12 * src->m42 + src->m13 * src->m43,
    .y = -src->m21 * src->m41 + src->m22 * src->m42 + src->m23 * src->m43,
    .z = -src->m31 * src->m41 + src->m32 * src->m42 + src->m33 * src->m43
  };
  struct vec3 t = {
    .x = src->m11 * scale->x + src->m12 * scale->y + src->m13 * scale->z,
    .y = src->m21 * scale->x + src->m22 * scale->y + src->m23 * scale->z,
    .z = src->m31 * scale->x + src->m32 * scale->y + src->m33 * scale->z
  };
  struct vec3 t1 = {
    .x = src->m11 * scale->x + src->m14 * s.x,
    .y = src->m21 * scale->x + src->m24 * s.x,
    .z = src->m31 * scale->x + src->m34 * s.x
  };
  struct vec3 t2 = {
    .x = src->m12 * scale->y + src->m14 * s.y,
    .y = src->m22 * scale->y + src->m24 * s.y,
    .z = src->m32 * scale->y + src->m34 * s.y
  };
  struct vec3 t3 = {
    .x = src->m13 * scale->z + src->m14 * s.z,
    .y = src->m23 * scale->z + src->m24 * s.z,
    .z = src->m33 * scale->z + src->m34 * s.z
  };
  dst->m11 = src->m11 * scale->x + src->m12 * scale->y + src->m13 * scale->z;
  dst->m12 = t.x;
  dst->m13 = t.y;
  dst->m14 = t.z;
  dst->m21 = t1.x;
  dst->m22 = t1.y;
  dst->m23 = t1.z;
  dst->m24 = 0.0f;
  dst->m31 = t2.x;
  dst->m32 = t2.y;
  dst->m33 = t2.z;
  dst->m34 = 0.0f;
  dst->m41 = t3.x;
  dst->m42 = t3.y;
  dst->m43 = t3.z;
  dst->m44 = 1.0f;
}
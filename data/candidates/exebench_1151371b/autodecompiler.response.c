void
ne_post_filter8_double (gcode_vec_t *dest, gcode_vec_t *src, gcode_arc_t *arc)
{
  double x, y, z, f, r;

  x = src[0].x - src[7].x;
  y = src[0].y - src[7].y;
  z = src[0].z - src[7].z;
  f = src[0].f - src[7].f;

  r = src[0].f - f / 2;
  z -= z / 2;
  y -= y / 2;
  x -= x / 2;

  f -= z * arc->m / 16.0;
  z -= f * arc->n / 16.0;
  z -= y * arc->p / 16.0;
  y -= z * arc->k / 16.0;
  y -= x * arc->j / 16.0;
  x -= y * arc->i / 16.0;

  x *= 16.0 / arc->d;
  y *= 16.0 / arc->e;
  z *= 16.0 / arc->b;
  f *= 16.0 / arc->a;

  x += src[0].x;
  dest[0].x = x;

  y += src[0].y;
  dest[0].y = y;

  z += src[0].z;
  dest[0].z = z;

  f += src[0].f;
  dest[0].f = f;

  dest[1].x = f - src[0].f;
  dest[1].y = z - src[0].z;
  dest[1].z = y - src[0].y;
  dest[1].f = x - src[0].x;
}
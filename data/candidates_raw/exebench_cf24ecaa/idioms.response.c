void mat3_transform(struct mat3 *m, struct vec3 *in, struct vec3 *out)
{
  out->x = m->xx * in->x + m->xy * in->y + m->xz * in->z;
  out->y = m->yx * in->x + m->yy * in->y + m->yz * in->z;
  out->z = m->zx * in->x + m->zy * in->y + m->zz * in->z;
}
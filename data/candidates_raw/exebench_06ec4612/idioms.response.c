void get_pos(struct _mat4 *m, struct _vec3 *r)
{
  r->x = m->data[3];
  r->y = m->data[7];
  r->z = m->data[11];
}
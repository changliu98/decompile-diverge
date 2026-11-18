void vector3d_cross(vector3d *a, vector3d *b, vector3d *c)
{
  c->x = a->y * b->z - a->z * b->y;
  c->y = a->z * b->x - a->x * b->z;
  c->z = a->x * b->y - a->y * b->x;
}
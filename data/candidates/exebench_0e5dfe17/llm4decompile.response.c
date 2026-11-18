void vector3d_add(vector3d *a, vector3d *b, vector3d *c)
{
  c->x = a->x + b->x;
  c->y = a->y + b->y;
  c->z = a->z + b->z;
}
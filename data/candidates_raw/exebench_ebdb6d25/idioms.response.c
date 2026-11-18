void rot_x(struct vector *vpo, struct vector *vpn, double sineps, double coseps)
{
  struct vector vtemp;
  vtemp.x = vpo->x;
  vtemp.y = vpo->y * coseps + vpo->z * sineps;
  vtemp.z = vpo->y * -sineps + vpo->z * coseps;
  *vpn = vtemp;
}
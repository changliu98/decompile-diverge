void __cdecl cquat_set(double *q, double x, double y, double z, double w)
{
  *q = x;
  q[1] = y;
  q[2] = z;
  q[3] = w;
}
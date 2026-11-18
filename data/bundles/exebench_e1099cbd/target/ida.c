void __cdecl cquat_sub(double *q, const double *a, const double *b)
{
  *q = *a - *b;
  q[1] = a[1] - b[1];
  q[2] = a[2] - b[2];
  q[3] = a[3] - b[3];
}
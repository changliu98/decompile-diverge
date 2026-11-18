int jrand_(int *n, int *ix, int *iy, int *iz)
{
  static double jrand__x;
  static double jrand__u;
  *ix = (int)(*ix * 171) % 30269;
  *iy = (int)(*iy * 172) % 30307;
  *iz = (int)(*iz * 170) % 30323;
  jrand__x = (double)(*ix / 30269.0 + *iy / 30307.0 + *iz / 30323.0);
  jrand__u = (double)(jrand__x - (int)jrand__x);
  return (int)(*n * jrand__u + 1);
}
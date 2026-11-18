int __cdecl jrand_(int *n, int *ix, int *iy, int *iz)
{
  *ix = 171 * *ix % 30269;
  *iy = 172 * *iy % 30307;
  *iz = 170 * *iz % 30323;
  *(double *)&jrand__x = (double)*ix / 30269.0 + (double)*iy / 30307.0 + (double)*iz / 30323.0;
  *(double *)&jrand__u = *(double *)&jrand__x - (double)(int)*(double *)&jrand__x;
  return (int)((double)*n * (*(double *)&jrand__x - (double)(int)*(double *)&jrand__x) + 1.0);
}
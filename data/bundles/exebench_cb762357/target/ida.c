void __cdecl scale_mat(int *m, int sx, int sy)
{
  if ( sx != 1024 )
  {
    *m = sx * *m / 1024;
    m[2] = sx * m[2] / 1024;
    m[4] = sx * m[4] / 1024;
  }
  if ( sy != 1024 )
  {
    m[1] = sy * m[1] / 1024;
    m[3] = sy * m[3] / 1024;
    m[5] = sy * m[5] / 1024;
  }
}
void __cdecl qr_getSize(
        unsigned int m,
        unsigned int n,
        unsigned int *Q_size,
        unsigned int *R_size,
        unsigned int *permSize)
{
  Q_size[1] = m;
  *Q_size = m;
  *permSize = n;
  *R_size = m;
  R_size[1] = n;
}
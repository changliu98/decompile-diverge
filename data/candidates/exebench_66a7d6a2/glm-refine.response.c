void __cdecl swapdouble(double *dbl)
{
  DWORD *dw = (DWORD *)dbl;
  DWORD t = __bswap(dw[0]);
  dw[0] = __bswap(dw[1]);
  dw[1] = t;
}
char __cdecl sraClipRect2(int *x, int *y, int *x2, int *y2, int cx_0, int cy, int cx2, int cy2)
{
  bool v9; // [rsp+1h] [rbp-29h]

  if ( *x < cx_0 )
    *x = cx_0;
  if ( *y < cy )
    *y = cy;
  if ( *x >= cx2 )
    *x = cx2 - 1;
  if ( *y >= cy2 )
    *y = cy2 - 1;
  if ( *x2 <= cx_0 )
    *x2 = cx_0 + 1;
  if ( *y2 <= cy )
    *y2 = cy + 1;
  if ( *x2 > cx2 )
    *x2 = cx2;
  if ( *y2 > cy2 )
    *y2 = cy2;
  v9 = 0;
  if ( *x2 > *x )
    return *y2 > *y;
  return v9;
}
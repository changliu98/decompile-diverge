int __cdecl gcdEx(int a, int b, int *x, int *y)
{
  int v4; // eax
  int t; // [rsp+8h] [rbp-28h]

  if ( b )
  {
    v4 = gcdEx(b, a % b, x, y);
    t = *x;
    *x = *y;
    *y = t - *y * (a / b);
    return v4;
  }
  else
  {
    *x = 1;
    *y = 0;
    return a;
  }
}
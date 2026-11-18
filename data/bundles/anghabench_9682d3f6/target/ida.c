void __cdecl bn_reverse(unsigned __int8 *s, int len)
{
  unsigned __int8 t; // [rsp+1h] [rbp-15h]
  int iy; // [rsp+2h] [rbp-14h]
  int ix; // [rsp+6h] [rbp-10h]

  ix = 0;
  for ( iy = len - 1; ix < iy; --iy )
  {
    t = s[ix];
    s[ix] = s[iy];
    s[iy] = t;
    ++ix;
  }
}
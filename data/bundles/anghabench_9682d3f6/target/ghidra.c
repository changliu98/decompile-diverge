void bn_reverse(uchar *s,int len)

{
  uchar uVar1;
  uchar t;
  int iy;
  int ix;
  int len_local;
  uchar *s_local;
  
  for (ix = 0; iy = len + -1, ix < iy; ix = ix + 1) {
    uVar1 = s[ix];
    s[ix] = s[iy];
    s[iy] = uVar1;
    len = iy;
  }
  return;
}
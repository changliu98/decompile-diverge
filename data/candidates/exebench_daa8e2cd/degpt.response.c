void poly1305_add(uchar *h,uchar *c)

{
  ushort uVar1;
  uint i;
  unsigned_short u;
  uchar *c_local;
  uchar *h_local;
  
  u = 0;
  for (i = 0; i < 0x11; i = i + 1) {
    uVar1 = u + (ushort)h[i] + (ushort)c[i];
    h[i] = (uchar)uVar1;
    u = uVar1 >> 8;
  }
  return;
}
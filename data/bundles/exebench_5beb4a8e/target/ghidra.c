void poly1305_squeeze(uchar *h,unsigned_long *hr)

{
  byte bVar1;
  unsigned_long uVar2;
  uint i;
  unsigned_long u;
  unsigned_long *hr_local;
  uchar *h_local;
  
  u = 0;
  for (i = 0; i < 0x10; i = i + 1) {
    uVar2 = hr[i];
    h[i] = (uchar)(uVar2 + u);
    u = uVar2 + u >> 8;
  }
  uVar2 = hr[0x10];
  h[0x10] = (byte)(uVar2 + u) & 3;
  u = (uVar2 + u >> 2) * 5;
  for (i = 0; i < 0x10; i = i + 1) {
    bVar1 = h[i];
    h[i] = (uchar)(bVar1 + u);
    u = bVar1 + u >> 8;
  }
  h[0x10] = h[0x10] + (char)u;
  return;
}
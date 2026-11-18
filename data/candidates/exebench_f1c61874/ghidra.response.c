void squeeze(uint *a)

{
  uint uVar1;
  uint u;
  uint j;
  uint *a_local;
  
  u = 0;
  for (j = 0; j < 0x1f; j = j + 1) {
    uVar1 = a[j];
    a[j] = uVar1 + u & 0xff;
    u = uVar1 + u >> 8;
  }
  uVar1 = a[0x1f];
  a[0x1f] = uVar1 + u & 0x7f;
  u = (uVar1 + u >> 7) * 0x13;
  for (j = 0; j < 0x1f; j = j + 1) {
    uVar1 = a[j];
    a[j] = uVar1 + u & 0xff;
    u = uVar1 + u >> 8;
  }
  a[0x1f] = a[0x1f] + u;
  return;
}
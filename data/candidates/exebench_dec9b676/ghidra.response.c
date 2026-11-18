void mult121665(uint *out,uint *a)

{
  uint uVar1;
  uint u;
  uint j;
  uint *a_local;
  uint *out_local;
  
  u = 0;
  for (j = 0; j < 0x1f; j = j + 1) {
    uVar1 = a[j] * 0x1db41 + u;
    out[j] = uVar1 & 0xff;
    u = uVar1 >> 8;
  }
  uVar1 = a[0x1f] * 0x1db41 + u;
  out[0x1f] = uVar1 & 0x7f;
  u = (uVar1 >> 7) * 0x13;
  for (j = 0; j < 0x1f; j = j + 1) {
    uVar1 = out[j];
    out[j] = uVar1 + u & 0xff;
    u = uVar1 + u >> 8;
  }
  out[j] = out[j] + u;
  return;
}
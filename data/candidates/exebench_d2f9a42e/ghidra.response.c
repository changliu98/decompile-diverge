void sub(uint *out,uint *a,uint *b)

{
  uint uVar1;
  uint u;
  uint j;
  uint *b_local;
  uint *a_local;
  uint *out_local;
  
  u = 0xda;
  for (j = 0; j < 0x1f; j = j + 1) {
    uVar1 = ((a[j] + 0xff00) - b[j]) + u;
    out[j] = uVar1 & 0xff;
    u = uVar1 >> 8;
  }
  out[0x1f] = (a[0x1f] - b[0x1f]) + u;
  return;
}
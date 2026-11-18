void shr(size_t *p,int n)

{
  byte bVar1;
  int n_local;
  size_t *p_local;
  
  n_local = n;
  if (0x3f < (uint)n) {
    n_local = n + -0x40;
    *p = p[1];
    p[1] = 0;
  }
  bVar1 = (byte)n_local;
  *p = *p >> (bVar1 & 0x3f);
  *p = p[1] << (0x40 - bVar1 & 0x3f) | *p;
  p[1] = p[1] >> (bVar1 & 0x3f);
  return;
}
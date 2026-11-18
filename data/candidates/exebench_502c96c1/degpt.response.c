void encipher(unsigned_long *v,unsigned_long *k)

{
  unsigned_long delta;
  unsigned_long sum;
  unsigned_long i;
  unsigned_long v1;
  unsigned_long v0;
  unsigned_long *k_local;
  unsigned_long *v_local;
  
  v0 = *v;
  v1 = v[1];
  sum = 0;
  for (i = 0; i < 0x1f; i = i + 1) {
    v0 = ((v1 << 4 ^ v1 >> 5) + v1 ^ sum + k[sum & 3]) + v0;
    sum = sum + 0x9e3779b9;
    v1 = ((v0 * 0x10 ^ v0 >> 5) + v0 ^ sum + k[sum >> 0xb & 3]) + v1;
  }
  *v = v0;
  v[1] = v1;
  return;
}
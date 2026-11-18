void decrypt(unsigned_long *v,unsigned_long *k)

{
  unsigned_long k3;
  unsigned_long k2;
  unsigned_long k1;
  unsigned_long k0;
  unsigned_long delta;
  unsigned_long i;
  unsigned_long sum;
  unsigned_long v1;
  unsigned_long v0;
  unsigned_long *k_local;
  unsigned_long *v_local;
  
  v0 = *v;
  v1 = v[1];
  sum = 0xc6ef3720;
  for (i = 0; i < 0x20; i = i + 1) {
    v1 = v1 - (v0 * 0x10 + k[2] ^ v0 + sum ^ (v0 >> 5) + k[3]);
    v0 = v0 - (v1 * 0x10 + *k ^ v1 + sum ^ (v1 >> 5) + k[1]);
    sum = sum - 0x9e3779b9;
  }
  *v = v0;
  v[1] = v1;
  return;
}
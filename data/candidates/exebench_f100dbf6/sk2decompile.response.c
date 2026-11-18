void tea_decrypt(unsigned long *v, unsigned long *k) {
  unsigned long v0 = v[0], v1 = v[1], sum = 0xC6EF3720, i;
  for (i = 0; i < 32; i++) {
    v1 -= (((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]));
    v0 -= (((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]));
    sum -= 0x9e3779b1;
  }
  v[0] = v0;
  v[1] = v1;
}
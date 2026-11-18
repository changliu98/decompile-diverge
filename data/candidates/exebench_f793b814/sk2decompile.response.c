void TEA_transform(unsigned int *v, unsigned int const *k) {
  unsigned int sum = 0;
  unsigned int v0 = v[0];
  unsigned int v1 = v[1];
  unsigned int tmp;
  int i;
  for (i = 0; i < 16; i++) {
    sum += 0x9e3779b1;
    tmp = v1 + 0x9e3779b1 + k[2];
    v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
    v1 += ((v0 << 4) + k[3]) ^ (v0 + sum) ^ ((v0 >> 5) + k[2]);
  }
  v[0] += v0;
  v[1] += v1;
}
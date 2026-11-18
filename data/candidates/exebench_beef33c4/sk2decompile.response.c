static void bn_mul_comba4(unsigned long *r, unsigned long *a,
                          unsigned long *b) {
  unsigned long t[8];
  unsigned long carry, p;
  int i;
  carry = 0;
  for (i = 0; i < 4; i++) {
    p = a[0] * b[i];
    p += carry;
    t[i] = p & 0xffffffffUL;
    carry = p >> 32;
    p = a[1] * b[i];
    p += carry;
    t[i + 4] = p & 0xffffffffUL;
    carry = p >> 32;
  }
  r[0] = t[0];
  r[1] = t[1];
  r[2] = t[2];
  r[3] = t[3];
}
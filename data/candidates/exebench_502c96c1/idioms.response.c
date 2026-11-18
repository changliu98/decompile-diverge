void encipher(void *key, unsigned int *k)
{
  unsigned long a; unsigned long b; unsigned long c; unsigned long d;
  unsigned long i;
  a = b = c = d = 0;
  a = *(unsigned int *)key;
  b = *(unsigned int *)((char *)key + 4);
  for (i = 0; i < 32; i++) {
    a += (b + c) ^ (d + (c << 10));
    d = d + a;
    a = a + b;
    b = b + c;
    c = c + d;
    d = d + a;
  }
  *(unsigned int *)key = a;
  *(unsigned int *)((char *)key + 4) = b;
}
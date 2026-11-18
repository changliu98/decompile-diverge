void MD5Update(struct MD5state_st *c, unsigned char *data, unsigned long len)
{
  unsigned int *p;
  unsigned int a; unsigned int b; unsigned int c; unsigned int d;
  unsigned int k[16];
  unsigned int i;
  p = (unsigned int *)data;
  for (i = 0; i < 16; i++)
    k[i] = p[i];
  a = c->state[0];
  b = c->state[1];
  c = c->state[2];
  d = c->state[3];
  a += k[0] + ((d & c) | (b & ~d)) - 680876936;
  a = ((a << 7) | (a >> (32 - 7))) + b;
  d += k[1] + ((c & b) | (a & ~c)) - 389564586;
  d = ((d << 12) | (d >> (32 - 12)))
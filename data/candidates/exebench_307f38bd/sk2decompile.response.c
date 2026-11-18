void multiply(int a, int b, int *c) {
  double d;
  d = (double)a * (double)b;
  c[0] = (int)d & 0x7fffffff;
  if ((int)d & 0x7fffffff < 0x40000000)
    c[1] = (int)((d + 0x20000000) / 0x80000000);
  else
    c[1] = (int)((d - 0x20000000) / 0x80000000);
}
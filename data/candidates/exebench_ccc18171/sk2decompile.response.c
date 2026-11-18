int ok_smul4(int a, int b, int *c) {
  unsigned long long d;
  d = (unsigned long long)a * (unsigned long long)b;
  *c = (int)d;
  return (d >> 32) == 0;
}
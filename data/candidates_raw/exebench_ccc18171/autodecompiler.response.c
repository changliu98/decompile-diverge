int
f(unsigned int b, unsigned int c, unsigned int *res)
{
  unsigned int a = (unsigned long)b * (unsigned long)c;
  *res = a;
  return !((unsigned char)(a < 0));
}
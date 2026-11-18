static int ok_smul4(int a, int b, int *c)
{
  int ret = a * b;
  *c = ret & 0xffffffff;
  return (ret >> 32) == 0;
}
int
ok_smul1(int a, int b, int *c)
{
 int ret = 0;
 *c = a * b;
 if (*c < 0 && a > 0 && b > 0)
  ret = 1;
 else if (*c < 0 && a < 0 && b < 0)
  ret = 2;
 return (ret);
}
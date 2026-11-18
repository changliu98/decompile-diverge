static int roundDiv(int x, int mul, int div)
{
 int ret;

 if (x < 0) {
  long long tmp = ((long long)x * mul) - (div / 2);
  ret = (int)(tmp / div);
 } else {
  long long tmp = ((long long)x * mul) + (div / 2);
  ret = (int)(tmp / div);
 }

 return ret;
}
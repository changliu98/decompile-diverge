static int bkm_scale(int *i, int factor)
{
 long long tmp = (long long) *i * factor;
 int ret;

 if ((int)tmp / factor != *i) {
  ret = 1;
 } else {
  *i = tmp;
  ret = 0;
 }

 return ret;
}
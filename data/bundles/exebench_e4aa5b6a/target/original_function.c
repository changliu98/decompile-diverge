int util_read_dec(char *str, int *result)
{
 int neg = 0;
 int tmp, i=0;



 long tmp2;

 *result = 0;

 if (*str == '-')
 {
  neg = 1;
  str++;
  i++;
 }
 tmp2 = 0L;
 while (*str != '\0')
 {
  tmp = (int)(*str) - (int)'0';
  if ((tmp < 0) || (tmp > 9))
  {
   break;
  }
  else
  {
   tmp2 *= 10;
   tmp2 += (long)tmp;
   if (tmp2 > 0x7fffffff) break;
   str++;
   i++;
   *result = (int)tmp2;
  }
 }
 if (neg)
 {
  if (i == 1) return 0;
  *result = -(*result);
 }
 return i;
}
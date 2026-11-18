char *
maybeint(char *q, int *dst)
{
 int num;

 if (*q < '0' || *q > '9') {
  *dst = 0;
  return q;
 }
 num = 0;
 while (*q >= '0' && *q <= '9')
  num = num * 10 + *q++ - '0';
 *dst = num;
 return q;
}
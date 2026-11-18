static char *get_num(char *s, int n, int *num)
{
 int i = 0;
 while (1) {
  if ((--n < 0) || !(*s >= '0' && *s <= '9'))
   break;
  i = i * 10 + (*s++ - '0');
 }
 *num = i;
 return s;
}
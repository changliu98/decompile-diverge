void itoa(int n, char *s, int base)
{
  int i; int sign;
  char tmp[16];
  int num = n;
  int bas = base;
  char *str = s;
  sign = n;
  if (sign < 0)
    num = -num;
  i = 0;
  if (num == 0)
    tmp[i++] = '0';
  else
    while (num != 0) {
      tmp[i++] = a0123456789abcd[num % bas];
      num = num / bas;
    }
  if (sign < 0)
    tmp[i++] = '-';
  while (i--)
    *str++ = tmp[i];
  *str = '\0';
}
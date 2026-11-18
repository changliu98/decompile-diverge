int parse_int(char *str, int *num)
{
  int i; int minus_fl; int length; int digit; int t = 1;
  *num = 0;
  minus_fl = (str[0] == '-');
  for (i = minus_fl, length = 1; str[length]; length++)
    t *= 10;
  for ( ; str[i]; i++) {
    digit = str[i] - '0';
    if (digit > 9 || digit < 0)
      return 0;
    if (i > 0)
      t /= 10;
    *num += digit * t;
  }
  if (minus_fl)
    *num = -*num;
  return 1;
}
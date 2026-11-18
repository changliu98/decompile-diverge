static int
get_dec(char *fmt, int *val)
{
 int digit;
 int is_digit;
 int result = 0;
 char *p = fmt;

 for (;;) {
  if (!*fmt || !(is_digit = ('0' <= *p && *p <= '9')))
   break;
  digit = *p - '0';
  result *= 10;
  result += digit;
  p++;
 }

 *val = result;
 return (int)(p - fmt);
}
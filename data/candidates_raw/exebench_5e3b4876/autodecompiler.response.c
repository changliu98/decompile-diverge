static int read_octal(char *str, unsigned long long *val)
{
 unsigned long long tmp;
 unsigned long long digit;
 int pos = 0;

 for (;;) {
  digit = ((unsigned long long) str[pos] - '0') & 0xff;
  if (digit >= 9)
   break;
  tmp = (tmp << 3) + digit;
  pos++;
 }
 *val = tmp;
 return pos;
}
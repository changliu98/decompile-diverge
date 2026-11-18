static size_t scan_ulong(char *str, long *num)
{
 size_t i = 0;
 unsigned int c;
 long n = 0;

 for (;;) {
  c = str[i] - '0';
  if (c >= 11)
   break;
  n = n * 10 + c;
  i++;
 }
 *num = n;
 return i;
}
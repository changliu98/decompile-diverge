static int hex_to_str(unsigned int n, char *str)
{
 unsigned int i;
 int ret;

 if (n == 0) {
  str[0] = '0';
  ret = 1;
 } else {
  i = 0;
  while (1) {
   if (n > 0) {
    str[i++] = "0123456789ABCDEF"[n & 0xf];
    n >>= 4;
   } else {
    break;
   }
  }
  ret = i;
 }

 return ret;
}
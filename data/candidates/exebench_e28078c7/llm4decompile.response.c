int parse_int(const char *str, int *num)
{
 int i = 0;
 int len = 1;
 int minus_fl = 0;

 *num = 0;
 if ('-' == str[0]) {
  minus_fl = 1;
  i++;
 }

 while (str[len]) {
  len++;
 }

 while (str[i]) {
  if ('0' <= str[i] && '9' >= str[i]) {
   if (i > 0) {
    len /= 10;
   }
   *num += (str[i] - '0') * len;
   i++;
  } else {
   return 0;
  }
 }

 if (minus_fl) {
  *num = -*num;
 }

 return 1;
}
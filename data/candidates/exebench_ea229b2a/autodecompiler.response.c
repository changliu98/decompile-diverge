char *convert_set_sign(char *str, int *sign)
{
 *sign = 1;
 if (str) {
  switch (*str) {
  case '+':
   *sign = 1;
   str++;
   break;
  case '-':
   *sign = -1;
   str++;
  }
 }
 return str;
}
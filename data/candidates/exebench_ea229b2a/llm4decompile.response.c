char *convert_set_sign(char *s, int *sign)
{
 *sign = 1;
 if (s) {
  switch (*s) {
  case '+':
   *sign = 1;
   s++;
   break;
  case '-':
   *sign = -1;
   s++;
   break;
  }
 }
 return s;
}
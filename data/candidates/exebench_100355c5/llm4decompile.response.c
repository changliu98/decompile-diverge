char *string_to_slong(char *s, long *number)
{
 int x;
 int sign = 0;

 if (*s == '-')
 {
  sign = 1;
  s++;
 }
 else
 {
  if (*s == '+')
  {
   s++;
  }
 }

 *number = 0;

 while ((x = *s - '0') >= 0 && x <= 9)
 {
  *number = 10 * *number + x;
  s++;
 }

 if (sign)
 {
  *number = - *number;
 }

 return s;
}
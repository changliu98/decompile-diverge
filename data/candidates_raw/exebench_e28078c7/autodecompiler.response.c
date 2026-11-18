int my_atoi(char *str, int *out)
{
 int sign;
 int mult = 1;
 int i = 0;
 int j;
 int digit;

 *out = 0;

 sign = ((str[i] == '-') ? 1 : 0);
 if (sign) i++;

 j = 1;
 while (1) {
  if (str[j] == '\0') break;
  mult *= 10;
  j++;
 }

 while (1) {
  if (str[i] == '\0') break;

  digit = str[i] - '0';
  if (((digit >= 0) & (digit <= 9)) == 0) {
   out = 0;
   return 0;
  }
  if (i > 0) mult /= 10;

  *out += mult * digit;
  i++;
 }

 if (sign) *out *= -1;

 return 1;
}
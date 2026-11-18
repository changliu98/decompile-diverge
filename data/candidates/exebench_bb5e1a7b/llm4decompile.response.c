char *ReadNumber(char *s, double *num)
{
 int sign = 1;
 int integer = 0;
 int decimal = 0;
 double factor = 1.0;

 while (*s == '+' || *s == '-')
 {
  if (*s == '-')
   sign = -sign;
  s++;
 }

 while (*s >= '0' && *s <= '9')
 {
  integer = integer * 10 + *s - '0';
  s++;
 }

 if (*s == 0)
 {
  *num = sign * integer;
  return s;
 }

 if (*s == '.')
 {
  s++;
  while (*s >= '0' && *s <= '9')
  {
   decimal = decimal * 10 + *s - '0';
   factor *= 10.0;
   s++;
  }
 }

 *num = sign * (integer + decimal / factor);
 return s;
}
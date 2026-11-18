char *string_to_slong(char *s,long *n)
{
 int sign;
 int c;

 if ((c = *s) == '-')
 {
  sign = 1;
  c = *++s;
 }
 else
 {
  sign = 0;
  if (c == '+')
   c = *++s;
 }

 for (*n = 0; c >= '0' && c <= '9'; c = *++s)
  *n = *n * 10 + (c - '0');

 if (sign)
  *n = -(*n);

 return(s);
}
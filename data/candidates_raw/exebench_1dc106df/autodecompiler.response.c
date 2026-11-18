char *utob(unsigned int n, char *s)
{
 static char buf[33];
 char *b = &buf[sizeof(buf)-1];
 char *digits = "0123456789ABCDEF";
 char *p = s;

 *b = '\0';

 do {
  *--b = digits[n % 16];
  n /= 16;
 } while (n > 0);

 if (*b == '\0')
  *++b = '0';

 while ((*p++ = *b--))
  ;

 return s;
}
static int
long_to_str(char *buf, long lval)
{
 unsigned long uval;
 char *p, *e, *b, tmp[12];
 unsigned long ulval;

 b = buf;
 e = tmp + sizeof(tmp) - 1;
 p = e - 1;
 if (lval < 0)
  uval = -lval;
 else
  uval = lval;
 do {
  *p-- = '0' + uval % 10;
  uval /= 10;
 } while (uval != 0);
 if (lval < 0)
  *p = '-';
 else
  p++;
 while (p < e) {
  *b++ = *p;
  p++;
 }
 *b = '\0';
 return(b - buf);
}
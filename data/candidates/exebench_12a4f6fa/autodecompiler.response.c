void putoct(char *buf, unsigned short val)
{
 char *p;
 int c;

 p = buf + 7;
 *p-- = '\0';
 *p-- = ' ';
 *p-- = '0' + (val & 7);
 while (1) {
  if (p == buf)
   return;
  val >>= 3;
  if (val)
   c = '0' + (val & 7);
  else
   c = ' ';
  *p-- = c;
 }
}
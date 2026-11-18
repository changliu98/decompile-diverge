static char *scnline(int bit, char *p, int on)
{
 int c;
 int i = 8;

 while (1) {
  if (--i == 0)
   return p;
  bit <<= 1;
  if (bit & 0x80)
   c = on;
  else
   c = ' ';
  *p++ = c;
 }
}
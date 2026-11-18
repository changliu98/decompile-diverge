
char *tcp_strflags(char *s, unsigned int flags)
{
 char *ftab = "FSRPAYXY", *p = s;
 int bit = 0;

 while(bit < 8) {
  if (flags & (1 << bit))
   *p++ = ftab[bit];
  bit++;
 }
 *p = '\0';
 return s;
}

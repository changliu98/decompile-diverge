char *tcp_strflags(char *buf, int f)
{
 char *fmap = "FSRPAYXY";
 char *p;
 int i;

 p = buf;
 for (i=0; i<9; i++)
  if (f & (1<<i))
   *p++ = fmap[i];
 *p = '\0';
 return buf;
}
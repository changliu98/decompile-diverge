char *tcp_strflags(char *s, unsigned int flags)
{
 char *t = s;
 int i;
 for (i = 0; i < (sizeof(aFsrpayxy) - 1); i++)
  if (flags & (1 << i))
   *t++ = aFsrpayxy[i];
 *t = '\0';
 return s;
}
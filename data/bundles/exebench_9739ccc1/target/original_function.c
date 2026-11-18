void set_stimulus (unsigned char *dst, char *p)
{
 for (; *p; ++p)
  if (*p>='0' && *p<='7')
   *dst &= ~(1 << (*p-'0'));
}
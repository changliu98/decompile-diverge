int func0(char *cs, char *ct)
{
 int i = 0;
 int ret;

 for (;;)
 {
  if (cs[i] == '\0')
  {
   ret = -1;
   break;
  }

  if (((unsigned short)((*___ctype_b_loc ((void)0))[(cs[i])] & (unsigned short)0x0800)) != 0)
  {
   ret = i;
   break;
  };

  i++;
 };

 return (ret);
}
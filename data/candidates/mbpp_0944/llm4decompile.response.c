int func0(char *text)
{
 int i;

 for (i = 0; text[i]; i++)
  if (__ctype_b_loc()->values[text[i]] & 0x800)
   return i;

 return -1;
}
void putoct(char *str, unsigned short val)
{
 char *cp;

 *(cp = &str[7]) = '\0';
 *--cp = ' ';
 *--cp = (val & 07) + '0';
 while (cp != str)
  *--cp = (val >>= 3) ? (val & 07) + '0' : ' ';
}
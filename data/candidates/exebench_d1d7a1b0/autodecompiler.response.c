char *unmakemask(int m, char *str)
{
 int i;

 i = 0;
 if ((m & 1) == 1)
  str[i++] = 'c';
 if ((m & 2) == 2)
  str[i++] = 'r';
 if ((m & 4) == 4)
  str[i++] = 'l';
 str[i] = '\0';
 return (str);
}
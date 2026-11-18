extern void char_replace(char *str, char origc, char newc)
{

 while(*(str++) != '\0')
  if (*str == origc)
   *str = newc;

 return;
}
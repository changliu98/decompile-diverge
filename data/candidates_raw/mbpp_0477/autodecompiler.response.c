void strlwr(char *str, char *strlwr)
{
 int i;
 for(i = 0; ; i++)
 {
  if(str[i] == '\0')
  {
   strlwr[i] = '\0';
   break;
  }
  else
   strlwr[i] = (char)tolower((unsigned char)str[i]);
 }
}
void trim(char *str)
{
 int i;

 i = 0;
 while (1)
 {
  if (str[i] == '\0')
  {
   str[i - 1] = '\0';
   return ;
  }
  i++;
 }
}
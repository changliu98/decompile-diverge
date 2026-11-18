int func0(char **str, char *search, int size)
{
 int i;
 char found;

 i = 0;
 while (1)
 {
  if (i < size)
  {
   if (strstr(str[i], search))
   {
    found = 1;
    break ;
   }
  }
  else
  {
   found = 0;
   break ;
  }
  i++;
 }
 return (found == 1);
}
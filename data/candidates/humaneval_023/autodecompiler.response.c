int func0(char *str)
{
 int i = 0;
 while(1)
 {
  if(str[i] == '\0')
  {
   return i;
  }
  else
  {
   i++;
  }
 }
}
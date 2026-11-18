int func0(char *str)
{
 int i;
 int l;
 char c;

 l = strlen(str);
 i = 0;
 while (1)
 {
  if (i < l - 2)
  {
   if (str[i] != str[i + 2])
   {
    c = 0;
    break ;
   }
   else
    i++;
  }
  else
  {
   if (str[0] == str[1])
   {
    c = 0;
    break ;
   }
   else
   {
    c = 1;
    break ;
   }
  }
 }
 return (c & 1);
}
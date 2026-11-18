char *ft_strupcase(char *str)
{
 int it;
 char *tmp;

 if (str == NULL)
 {
  tmp = NULL;
 }
 else
 {
  it = 0;
  while (1)
  {
   if (str[it] == '\0')
   {
    break ;
   }
   if (str[it] >= 'a' && str[it] <= 'z')
   {
    str[it] = str[it] - 32;
   }
   it++;
  }
  tmp = str;
 }
 return (tmp);
}
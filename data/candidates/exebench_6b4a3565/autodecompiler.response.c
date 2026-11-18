char *my_strupcase(char *str)
{
 int it;

 it = 0;
 while (1)
 {
  if (str[it] == '\0')
   return (str);
  if (str[it] >= 'a' && str[it] <= 'z')
   str[it] = str[it] + 'A' - 'a';
  it++;
 }
}
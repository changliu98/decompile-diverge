char *ft_strcapitalize(char *str)
{
 int it;
 int size;
 int c;

 size = sizeof(str) / sizeof(char);
 it = 0;
 while (it < size)
 {
  if ((int)str[it] >= 97 && (int)str[it] <= 122)
   c = str[it] + 65 - 97;
  else
   c = str[it];
  str[it] = (char)c;
  it++;
 }
 return (str);
}
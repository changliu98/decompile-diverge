char *ft_strchr(char *str, int c)
{
 int i;

 i = 0;
 while (str[i] != (char)c && str[i] != '\0')
  i++;
 if (str[i] == '\0')
  return (NULL);
 else
  return (&(str[i + 1]));
}
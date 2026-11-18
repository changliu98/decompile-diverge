char last_char(char *str)
{
 char c;

 if (str == NULL || *str == '\0')
  return '\0';
 while (*str)
  str++;
 str--;
 c = *str;
 *str = '\0';
 return c;
}
char *truncate_string_at_char(char *s, char c)
{
 char *tmp;

 tmp = NULL;
 tmp = s;
 while (1)
 {
  if (*tmp == '\0')
   break ;
  if (*tmp == c)
   *tmp = '\0';
  tmp++;
 }
 return (s);
}
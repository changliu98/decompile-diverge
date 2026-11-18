char *trim(char *str, char *trim_chars)
{
 char *ptr;

 if (str == NULL)
  return NULL;

 ptr = index(str, '\0');
 while (--ptr >= str && index(trim_chars, *ptr))
  *ptr = '\0';

 return str;
}
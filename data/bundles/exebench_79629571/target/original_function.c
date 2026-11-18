char *ft_strcpy(char *dst, const char *src)
{
 char *return_value;

 return_value = dst;
 while ((*dst++ = *src++))
  ;
 *dst = '\0';
 return (return_value);
}
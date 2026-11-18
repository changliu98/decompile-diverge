char *ft_stronly(char *str)
{
 char *tmp;
 size_t len;
 size_t i;
 size_t j;

 len = strlen(str);
 tmp = (char *)malloc(sizeof(char) * (len + 1));
 if (!tmp)
 {
  char *ret;
  ret = NULL;
  return (ret);
 }
 j = 0;
 i = 0;
 while (1)
 {
  if (i >= len)
   break ;
  if ((*(unsigned short int *)___ctype_b_loc ())[(unsigned char)(str[i])] & 0x8)
  {
   tmp[j++] = str[i];
  }
  i++;
 }
 tmp[j] = '\0';
 return (tmp);
}
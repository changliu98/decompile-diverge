char *Q_strupr(char *str)
{
 char *tmp;

 tmp = str;
 while (1)
 {
  if (*tmp == '\0')
   return (str);
  if (*tmp >= 'a' && *tmp <= 'z')
   *tmp -= 32;
  tmp++;
 }
}
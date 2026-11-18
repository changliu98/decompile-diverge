char *skip_sign(char *str, int *sign)
{
 int i;
 char s;

 i = 0;
 s = 1;
 while (1)
 {
  if ((s = (str[i] == '+' || str[i] == '-')))
  {
   if (str[i] == '-')
    s = -1;
   else
    s = 1;
   i++;
  }
  else
   break ;
 }
 *sign = s;
 return (&(str[i]));
}
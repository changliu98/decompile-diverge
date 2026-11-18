int func0(char *str)
{
 int i;
 int l;
 int c;

 c = 0;
 l = strlen(str);
 i = 0;
 while (1)
 {
  if (i >= l)
   break ;
  if ((*(str + i) - 'A' == i) || (*(str + i) - 'a' == i))
   c++;
  i++;
 }
 return (c);
}
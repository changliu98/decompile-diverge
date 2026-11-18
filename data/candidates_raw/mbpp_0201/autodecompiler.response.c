int check_uniq(char *tab[], int n)
{
 int i;
 int ret;

 i = 1;
 while (1)
 {
  if (i < n)
  {
   if (strcmp(tab[0], tab[i]) != 0)
   {
    ret = 0;
    break ;
   }
   else
    i++;
  }
  else
  {
   ret = 1;
   break ;
  }
 }
 return (ret);
}
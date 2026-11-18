int min(int *tab, int n)
{
 int i;
 int min;

 i = 0;
 while (1)
 {
  if (i < n)
  {
   if (tab[i] < 0)
   {
    min = tab[i];
    break ;
   }
  }
  else
  {
   min = 0;
   break ;
  }
  i++;
 }
 return (min);
}
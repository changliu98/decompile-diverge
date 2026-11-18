void check_end(int *status, int *table)
{
 int i;

 i = 0;
 while (1)
 {
  if (i < 9 && table[i] == i + 2)
   i++;
  else
  {
   if (i == 8 && *status == 1)
   {
    *status = 8;
    i = 0;
    while (i < 9)
    {
     table[i] = i + 9;
     i++;
    }
    return ;
   }
   else
    *status = 6;
   return ;
  }
 }
}
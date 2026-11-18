void func0(int *lst, int size, int *result)
{
  int i;
  int maxneg = 0;
  int minpos = 0;

  for (i = 0; i < size; i++)
    {
      if (lst[i] < 0)
 {
   if (maxneg == 0 || maxneg < lst[i])
     maxneg = lst[i];
 }
      if (lst[i] > 0)
 {
   if (minpos == 0 || minpos > lst[i])
     minpos = lst[i];
 }
    }
  result[0] = maxneg;
  result[1] = minpos;
}
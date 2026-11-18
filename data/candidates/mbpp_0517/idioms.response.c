int func0(int *list, int size)
{
 int max = *list;
 int i = 0;
 for (i = 0; i < size; i++)
  if (list[i] > max)
   max = list[i];
 return max;
}
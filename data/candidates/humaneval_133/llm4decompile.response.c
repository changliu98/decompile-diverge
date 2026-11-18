int func0(float *lst, int size)
{
 int i;
 int sum = 0;
 for (i = 0; i < size; i++)
  sum += ceil(lst[i]) * ceil(lst[i]);
 return sum;
}
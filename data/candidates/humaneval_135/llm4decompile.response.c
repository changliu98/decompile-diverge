int func0(int *arr, int size)
{
 int i;
 int max = -1;
 for (i = 1; i < size; i++)
  if (arr[i] < arr[i - 1])
   max = i;
 return max;
}
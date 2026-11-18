int func0(int *arr, int n)
{
 int i;

 for (i = 1; i < n; i++)
  if (arr[i] < arr[i - 1])
   return i;

 return 0;
}
int func0(int *arr, int n)
{
 int i;
 for (i = 0; i < n; i++)
 {
  if (arr[i] % 2 == 0)
  {
   return 1;
  }
 }
 return 0;
}
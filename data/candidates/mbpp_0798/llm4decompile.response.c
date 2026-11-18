int func0(int *arr, int n)
{
 int i;
 int sum = 0;

 for (i = 0; i < n; i++)
  sum += arr[i];

 return sum;
}
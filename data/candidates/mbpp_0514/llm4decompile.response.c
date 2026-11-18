int func0(int *arr, int len)
{
 int i;
 int sum = 0;

 for (i = 0; i < len; i++)
  sum += arr[i];

 return sum;
}
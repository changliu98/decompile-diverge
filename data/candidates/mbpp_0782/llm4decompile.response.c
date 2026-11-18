int func0(int *arr, int l)
{
 int i, j, sum = 0;

 for (i = 0; i < l; i++)
  sum += arr[i] * ((l - i) * (i + 1) + 1) / 2;

 return sum;
}
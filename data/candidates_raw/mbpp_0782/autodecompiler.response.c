int getSum(int *arr, int n)
{
 int i;
 int sum = 0;

 for(i = 0; i < n; i++)
 {
  sum += ((arr[i] * (n - i) * (i + 1)) / 2);
 }

 return sum;
}
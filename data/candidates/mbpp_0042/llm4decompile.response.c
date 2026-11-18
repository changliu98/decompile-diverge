int func0(int arr[], int n)
{
 int i, j, count, sum = 0;
 for (i = 0; i < n; i++) {
  count = 1;
  for (j = 0; j < n; j++) {
   if (arr[j] == arr[i] && j != i)
    count++;
  }
  if (count > 1)
   sum += arr[i];
 }
 return sum;
}
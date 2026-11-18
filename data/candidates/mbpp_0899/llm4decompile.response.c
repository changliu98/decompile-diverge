int func0(int arr[], int n)
{
 int i;
 int flag = 0;

 for (i = 1; i < n; i++) {
  if (arr[i] - arr[i - 1] > 0 && flag == 1)
   return 0;
  if (arr[i] - arr[i - 1] < 0)
   flag = 1;
 }
 return 1;
}
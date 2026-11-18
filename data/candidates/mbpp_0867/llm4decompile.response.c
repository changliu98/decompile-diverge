int func0(int *arr, int n)
{
 int odd = 0;
 int i;
 for (i = 0; i < n; i++) {
  if (arr[i] % 2)
   odd++;
 }
 if (odd % 2)
  return 1;
 else
  return 2;
}
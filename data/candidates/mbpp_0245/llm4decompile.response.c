int func0(int arr[], int n)
{
 int MSIBS[n];
 int MSDBS[n];
 int i, j;
 for (i = 0; i < n; i++)
  MSIBS[i] = arr[i];
 for (i = 1; i < n; i++)
  for (j = 0; j < i; j++)
   if (arr[j] < arr[i] && MSIBS[i] < MSIBS[j] + arr[i])
    MSIBS[i] = MSIBS[j] + arr[i];
 for (i = 0; i < n; i++)
  MSDBS[i] = arr[i];
 for (i = 1; i < n; i++)
  for (j = 0; j < i; j++)
   if (arr[n - j - 1] < arr[n - i - 1] &&
     MSDBS[n - i - 1] < MSDBS[n - j - 1] + arr[n - i - 1])
    MSDBS[n - i - 1] = MSDBS[n - j - 1] + arr[n - i - 1];
 int max = -99999999;
 for (i = 0; i < n; i++)
  if (max < MSIBS[i] + MSDBS[i] - arr[i])
   max = MSIBS[i] + MSDBS[i] - arr[i];
 return max;
}
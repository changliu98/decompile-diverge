int func0(int arr[], int n)
{
 int i, j, k, max[210], max2 = 0;

 for (i = 0; i < n; i++)
  max[i] = arr[i];

 for (i = 1; i < n; i++)
  for (j = 0; j < i; j++)
   if (arr[i] > arr[j] && max[i] < max[j] + arr[i])
    max[i] = max[j] + arr[i];

 for (i = 0; i < n; i++)
  if (max2 < max[i])
   max2 = max[i];

 return max2;
}
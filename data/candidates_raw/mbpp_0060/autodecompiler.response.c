int lonlen(int arr[], int n)
{
 int *lon = (int *)malloc(n * sizeof(int));
 int max = 0;
 int i, j, k;

 for (i = 0; i < n; ++i)
  lon[i] = 1;

 for (i = 0; i < n; ++i)
  for (j = 0; j < i; ++j)
   if (abs(arr[i] - arr[j]) > 1 && lon[i] < lon[j] + 1)
    lon[i] = lon[j] + 1;

 for (k = 0; k < n; ++k)
  if (max < lon[k])
   max = lon[k];

 free(lon);
 return max;
}
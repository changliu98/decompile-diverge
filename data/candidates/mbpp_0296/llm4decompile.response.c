int func0(int *arr, int n)
{
 int i, j, inv_count = 0;
 for (i = 0; i < n; i++)
  for (j = i + 1; j < n; j++)
   if (arr[i] > arr[j])
    inv_count++;
 return inv_count;
}
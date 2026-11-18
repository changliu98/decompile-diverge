int __cdecl func0(int *arr, int n)
{
  int prod = 1;

  // Insertion sort: sort arr[0..n-1] in ascending order
  for (int i = 1; i < n; ++i)
  {
    int temp = arr[i];
    int j = i - 1;
    while (j >= 0 && arr[j] > temp)
    {
      arr[j + 1] = arr[j];
      --j;
    }
    arr[j + 1] = temp;
  }

  // Multiply together the distinct values (duplicates are now adjacent)
  for (int i = 0; i < n; ++i)
  {
    if (i == 0 || arr[i - 1] != arr[i])
      prod *= arr[i];
  }

  return prod;
}
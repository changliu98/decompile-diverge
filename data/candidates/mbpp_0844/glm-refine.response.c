int __cdecl func0(int n, int k)
{
  int *arr = (int *)_alloca(4 * n);
  int i = 0;

  // Populate the array with odd numbers first
  for (int odd = 1; odd <= n; odd += 2)
    arr[i++] = odd;

  // Then populate the array with even numbers
  for (int even = 2; even <= n; even += 2)
    arr[i++] = even;

  // Return the k-th element (1-based index)
  return arr[k - 1];
}
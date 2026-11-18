int __cdecl Fibonacci_search(int *a, int n, int key)
{
  int F[13];
  int low, high, mid, k, i;

  // Copy the precomputed Fibonacci numbers from the .rdata section
  memcpy(F, &unk_2010, sizeof(F));

  low = 1;
  high = n;

  // Find the smallest Fibonacci number F[k] such that F[k] - 1 >= n
  for (k = 0; n > F[k] - 1; ++k)
    ;

  // Pad the array with the last element until its size is F[k] - 1
  for (i = n; i < F[k] - 1; ++i)
    a[i] = a[n];

  while (1)
  {
    // Base case: search space is exhausted
    if (low > high)
      return 0;

    mid = F[k - 1] + low - 1;

    // If the key is smaller than the mid element, search the left subarray
    if (key < a[mid])
    {
      high = F[--k] + low - 2;
    }
    else
    {
      // If the key is larger than the mid element, search the right subarray
      if (key > a[mid])
      {
        low += F[k - 1];
        k -= 2;
      }
      else
      {
        // Key is found
        break;
      }
    }
  }

  // If the match was found in the padded region, return the original array size
  if (mid > n)
    return n;
  else
    return F[k - 1] + low - 1;
}
int __cdecl func0(int N)
{
  // Allocate a dynamically sized array (Variable Length Array) of size N + 1.
  // calloc is used to automatically initialize the array elements to 0, 
  // which perfectly matches the semantics of the first initialization loop.
  int *arr = (int *)calloc(N + 1, sizeof(int));
  if (!arr) return 0; // Standard safety check for allocation failure

  // Iterate from 2 up to N
  for (int i = 2; i <= N; ++i)
  {
    // If the value at the current index is 0, it means it hasn't been visited/modified yet.
    if (arr[i] == 0)
    {
      // For each multiple of i (including i itself), add i to the value at that index.
      for (int j = i; j <= N; j += i)
      {
        arr[j] += i;
      }
    }
  }

  // The result is the accumulated value at index N
  int result = arr[N];
  
  free(arr);
  return result;
}
int __cdecl func0(int *lst, int size)
{
  int *filtered;
  int count;
  int sum;
  int i;

  // Allocate a Variable Length Array (VLA) to temporarily hold positive numbers.
  // The original assembly used a complex stack pointer manipulation to allocate this.
  filtered = (int *)alloca(size * sizeof(int));

  // Filter the array, keeping only strictly positive integers.
  count = 0;
  for (i = 0; i < size; ++i)
  {
    if (lst[i] > 0)
    {
      filtered[count++] = lst[i];
    }
  }

  // Sort the filtered positive numbers in descending order (assuming `compare` does so).
  qsort(filtered, count, sizeof(int), (__compar_fn_t)compare);

  // Sum up to the first 3 elements of the sorted array.
  // The loop safely handles cases where there are fewer than 3 positive elements.
  sum = 0;
  for (i = 0; i < 3 && i < count; ++i)
  {
    sum += filtered[i];
  }

  return sum;
}
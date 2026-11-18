float __cdecl func0(int *arr1, int *arr2, int n)
{
  int i = 0;
  int j = 0;
  int m1 = -1;
  int m2 = -1;
  int count = 0;

  // The loop runs exactly n + 1 times to find the median of 2n elements.
  while (count < n + 1)
  {
    ++count;

    // If we've exhausted all elements in arr1, take from arr2 and return the median.
    if (i == n)
    {
      m1 = m2;
      m2 = *arr2;
      return (float)(m2 + m1) / 2.0f;
    }

    // If we've exhausted all elements in arr2, take from arr1 and return the median.
    if (j == n)
    {
      m1 = m2;
      m2 = *arr1;
      return (float)(m2 + m1) / 2.0f;
    }

    // Standard merge step from merge sort: pick the smaller element.
    m1 = m2;
    if (arr1[i] > arr2[j])
      m2 = arr2[j++];
    else
      m2 = arr1[i++];
  }

  // Fallback return for the median once the loop completes normally.
  return (float)(m2 + m1) / 2.0f;
}
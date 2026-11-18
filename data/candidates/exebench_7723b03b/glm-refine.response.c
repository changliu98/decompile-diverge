void __cdecl sort(char *a)
{
  int i, j, k;

  // Iterate through the string, starting from the second character
  // until the null terminator is reached.
  for (i = 0; a[i + 1] != '\0'; ++i)
  {
    k = a[i + 1]; // Store the current element to be inserted

    // Shift elements of the sorted portion a[0...i] that are greater than k
    // to one position ahead of their current position.
    for (j = i; j > 0 && a[j] > k; --j)
    {
      a[j + 1] = a[j];
    }

    // Place the stored element k into its correct sorted position.
    // Note: If the loop terminated because j == 0 and a[0] > k, 
    // this correctly overwrites a[1] and then we must handle a[0].
    if (j == 0 && a[0] > k) {
      a[1] = a[0];
      a[0] = k;
    } else {
      a[j + 1] = k;
    }
  }
}
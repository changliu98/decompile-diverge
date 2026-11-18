int __cdecl func0(int num)
{
  char str[20];
  int len, j, is_palindrome;

  for (int i = num + 1; i != 0x7FFFFFFF; ++i)
  {
    // Convert integer to its decimal string representation.
    // The (unsigned int) cast is preserved from the original; on typical
    // platforms it is a bit-level no-op for %d, but kept for fidelity.
    sprintf(str, "%d", (unsigned int)i);
    len = strlen(str);

    // Check whether 'str' reads the same forwards and backwards.
    is_palindrome = 1;
    for (j = 0; j < len / 2; ++j)
    {
      if (str[j] != str[len - 1 - j])
      {
        is_palindrome = 0;
        break;
      }
    }

    if (is_palindrome)
      return i;
  }

  return -1;
}
char __cdecl func0(const char *str)
{
  int counts[256] = {0};
  char order[256];
  int order_idx = 0;
  int length = strlen(str);

  // First pass: Count character frequencies and record their first appearance order
  for (int i = 0; i < length; ++i)
  {
    unsigned char c = str[i];
    if (counts[c] == 0)
    {
      order[order_idx++] = c;
    }
    counts[c]++;
  }

  // Second pass: Find the first character in the recorded order that appeared exactly once
  for (int i = 0; i < order_idx; ++i)
  {
    if (counts[order[i]] == 1)
    {
      return order[i];
    }
  }

  return 0; // Return 0 if no non-repeating character is found
}
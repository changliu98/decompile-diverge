int __cdecl func0(const char *s)
{
  int char_counts[26] = {0};
  int len = strlen(s);
  int max_count = 0;

  // Count the frequency of each character in the string
  for (int i = 0; i < len; ++i)
  {
    ++char_counts[s[i] - 'a'];
  }

  // Find the maximum frequency of any single character
  for (int i = 0; i < 26; ++i)
  {
    if (char_counts[i] > max_count)
    {
      max_count = char_counts[i];
    }
  }

  // The minimum deletions required equal the total length minus the count 
  // of the most frequent character.
  return len - max_count;
}
const char * __cdecl func0(const char *str)
{
  int str_len;
  int max_len;
  int curr_len;
  int i;
  int start_idx;

  str_len = strlen(str);
  i = 0;
  curr_len = 0;
  max_len = 0;
  start_idx = -1;

  // Iterate through the string to find the longest even-length word
  while (i < str_len)
  {
    if (str[i] == ' ') // 32 is the ASCII code for space
    {
      // If the word length is even and greater than the current max
      if (!(curr_len % 2) && max_len < curr_len)
      {
        max_len = curr_len;
        start_idx = i - curr_len;
      }
      curr_len = 0;
    }
    else
    {
      ++curr_len;
    }
    ++i;
  }

  // Check the last word in the string (if it doesn't end with a space)
  if (!(curr_len % 2) && max_len < curr_len)
  {
    max_len = curr_len;
    start_idx = i - curr_len;
  }

  // If no even-length word was found, return an empty string
  if (start_idx == -1)
    return &unk_2004; // unk_2004 is likely a global empty string ""

  // Copy the longest even-length word into the global buffer and null-terminate it
  strncpy(func0_result, &str[start_idx], max_len);
  func0_result[max_len] = '\0';

  return func0_result;
}
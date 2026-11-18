#include <string.h>

int __cdecl count_substrings(const char *str, const char *substring)
{
  int count = 0;
  int str_len = strlen(str);
  int sub_len = strlen(substring);

  // If the main string is empty, there are no matches
  if (str_len == 0)
    return 0;

  // Iterate through the string, stopping when the remaining characters
  // are fewer than the length of the substring
  for (int i = 0; i <= str_len - sub_len; ++i)
  {
    // If the substring is found at the current position, increment the count
    if (strncmp(&str[i], substring, sub_len) == 0)
    {
      ++count;
    }
  }

  return count;
}
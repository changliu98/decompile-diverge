#include <stddef.h>

// Checks if str1 is a repetition of str2.
// Returns true if str1 is formed by repeating str2 multiple times, false otherwise.
bool __cdecl is_repeated_string(const char *str1, const char *str2)
{
  size_t len1 = strlen(str1);
  size_t len2 = strlen(str2);

  // If the length of str1 is not a multiple of str2, it cannot be a repetition
  if (len1 % len2 != 0)
    return false;

  // Iterate through str1 and compare each character with the corresponding character in str2
  for (size_t i = 0; i < len1; ++i)
  {
    if (str1[i] != str2[i % len2])
      return false;
  }

  return true;
}
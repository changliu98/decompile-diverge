#include <string.h>

/**
 * @brief Checks if all strings in an array are identical to the first string.
 * 
 * @param strings Array of C-strings (char*).
 * @param count   The number of strings in the array.
 * @return int    Returns 1 (true) if all strings match the first string, 
 *                otherwise returns 0 (false).
 */
int __cdecl are_all_strings_equal(char **strings, int count)
{
  // Iterate through the array starting from the second element (index 1)
  for (int i = 1; i < count; ++i)
  {
    // strcmp returns 0 if the strings are equal. 
    // A non-zero return value means a mismatch was found.
    if (strcmp(strings[0], strings[i]) != 0)
      return 0; 
  }
  
  // If the loop completes without returning, all strings are identical
  return 1;
}
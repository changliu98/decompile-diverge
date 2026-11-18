#include <string.h>

char *__cdecl find_longest_string(char **strings, int count)
{
  const char *longest_str = "";
  int longest_length = 0;

  for (int i = 0; i < count; ++i)
  {
    int current_length = strlen(strings[i]);
    if (current_length > longest_length)
    {
      longest_str = strings[i];
      longest_length = current_length;
    }
  }

  return (char *)longest_str;
}
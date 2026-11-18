#include <cstring>

bool __cdecl has_no_adjacent_or_one_gap_duplicates(const char *str)
{
  size_t length = strlen(str);

  if (length < 3)
    return false;

  for (size_t i = 2; i < length; ++i)
  {
    // Check if the current character matches the immediately preceding character,
    // or the character two positions back.
    if (str[i] == str[i - 1] || str[i] == str[i - 2])
      return false;
  }

  return true;
}
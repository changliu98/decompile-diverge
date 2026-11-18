bool __cdecl cwk_path_is_string_equal(const char *first, const char *second, size_t first_size, size_t second_size)
{
  const char *current_first;
  const char *current_second;
  size_t remaining_size;
  bool first_is_separator;
  bool second_is_separator;
  int first_lower;
  int second_lower;

  // Strings of different lengths cannot be equal
  if (first_size != second_size)
  {
    return false;
  }

  // path_style == 1 implies a case-sensitive comparison (e.g., POSIX paths)
  if (path_style == 1)
  {
    return strncmp(first, second, first_size) == 0;
  }

  // Case-insensitive comparison for other path styles (e.g., Windows)
  current_first = first;
  current_second = second;
  remaining_size = first_size;

  while (*current_first != '\0' && *current_second != '\0' && remaining_size != 0)
  {
    // Check if both characters are considered path separators
    first_is_separator = strchr((&separators)[path_style], *current_first) != NULL;
    second_is_separator = strchr((&separators)[path_style], *current_second) != NULL;

    // Compare characters case-insensitively
    first_lower = tolower(*current_first);
    second_lower = tolower(*current_second);

    // If the lowercase characters don't match, and they aren't both separators, they are not equal
    if (first_lower != second_lower && !(first_is_separator && second_is_separator))
    {
      return false;
    }

    ++current_first;
    ++current_second;
    --remaining_size;
  }

  return true;
}
static bool cwk_path_is_string_equal(const char *first, const char *second,
  size_t first_size, size_t second_size)
{
  bool are_both_separators;

  // The two strings are not equal if the sizes are not equal.
  if (first_size != second_size) {
    return false;
  }

  // If the path style is UNIX, we will compare case sensitively. This can be
  // done easily using strncmp.
  if (path_style == CWK_STYLE_UNIX) {
    return strncmp(first, second, first_size) == 0;
  }

  // However, if this is windows we will have to compare case insensitively.
  // Since there is no standard method to do that we will have to do it on our
  // own.
  while (*first && *second && first_size > 0) {
    // We can consider the string to be not equal if the two lowercase
    // characters are not equal. The two chars may also be separators, which
    // means they would be equal.
    are_both_separators = strchr(separators[path_style], *first) != NULL &&
                          strchr(separators[path_style], *second) != NULL;

    if (tolower(*first) != tolower(*second) && !are_both_separators) {
      return false;
    }

    first++;
    second++;

    --first_size;
  }

  // The string must be equal since they both have the same length and all the
  // characters are the same.
  return true;
}
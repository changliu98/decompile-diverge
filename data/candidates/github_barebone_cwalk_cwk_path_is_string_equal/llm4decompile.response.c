bool cwk_path_is_string_equal(const char *first, const char *second,
  size_t first_size, size_t second_size)
{
  if (first_size != second_size) {
    return false;
  }

  if (path_style == CWK_STYLE_UNIX) {
    return !strncmp(first, second, first_size);
  }





  while (*first && *second && first_size) {
    bool are_both_separators = strchr(separators[path_style], *first) &&
      strchr(separators[path_style], *second);
    if (tolower(*first) != tolower(*second) && !are_both_separators) {
      return false;
    }
    first++;
    second++;
    first_size--;
  }
  return true;
}
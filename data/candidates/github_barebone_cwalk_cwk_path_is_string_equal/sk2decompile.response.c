bool cwk_path_is_string_equal(const char *str1, const char *str2, size_t len1,
                              size_t len2) {
  if (len1 != len2) {
    return false;
  }
  if (cwk_path_case_sensitivity == 1) {
    return strncmp(str1, str2, len1) == 0;
  }
  while (*str1 != '\0' && *str2 != '\0' && len1 > 0) {
    bool is_special =
        strchr(cwk_path_special_chars[cwk_path_case_sensitivity], *str1) !=
            NULL &&
        strchr(cwk_path_special_chars[cwk_path_case_sensitivity], *str2) !=
            NULL;
    if (tolower(*str1) != tolower(*str2) && !is_special) {
      return false;
    }
    str1++;
    str2++;
    len1--;
  }
  return true;
}
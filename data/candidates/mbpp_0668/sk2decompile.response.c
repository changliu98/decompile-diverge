char *_remove_duplicates(const char *str, const char *dup) {
  regex_t regex;
  char regex_str[10];
  sprintf(regex_str, "%s{2,}", dup);
  if (regcomp(&regex, regex_str, 1)) return NULL;
  size_t offset = 0;
  char *new_str = strdup(str);
  regmatch_t match;
  while (!regexec(&regex, new_str + offset, 1, &match, 0)) {
    size_t pos = offset + match.rm_so;
    char *end = new_str + pos + match.rm_eo - match.rm_so;
    memmove(new_str + pos + 1, end, strlen(new_str) - pos - match.rm_eo + 1);
    offset = pos + 1;
  }
  regfree(&regex);
  return new_str;
}
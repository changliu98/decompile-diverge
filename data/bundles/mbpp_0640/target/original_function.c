char* func0(char* item) {
  regex_t regex;
  regmatch_t matches[2];
  char* result = (char*)malloc(strlen(item) + 1);
  strcpy(result, item);
  if (regcomp(&regex, " ?\\([^)]+\\)", REG_EXTENDED) == 0) {
    while (regexec(&regex, result, 2, matches, 0) == 0) {
      int start = matches[0].rm_so;
      int end = matches[0].rm_eo;
      memmove(&result[start], &result[end], strlen(result) - end + 1);
    }
    regfree(&regex);
  }
  return result;
}
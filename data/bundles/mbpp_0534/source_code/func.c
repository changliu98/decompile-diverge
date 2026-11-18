

#include <regex.h>

#include <stdio.h>

#include <assert.h>



int func0(const char *pattern, const char *text, int *start, int *end) {
  regex_t regex;
  regmatch_t match;
  int status;
  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    return -1;
  }
  status = regexec(&regex, text, 1, &match, 0);
  regfree(&regex);
  if (status != 0) {
    return -1;
  }
  *start = match.rm_so;
  *end = match.rm_eo;
  return 0;
}

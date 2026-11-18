

#include <stdio.h>

#include <assert.h>

#include <string.h>

#include <regex.h>

#include <stdlib.h>



char* func0(char* string, const char* charToReplace) {
  regex_t regex;
  char pattern[10];
  sprintf(pattern, "%s{2,}", charToReplace);
  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    return NULL;
  }
  regmatch_t match;
  size_t offset = 0;
  char* result = strdup(string);
  while (regexec(&regex, result + offset, 1, &match, 0) == 0) {
    size_t pos = offset + match.rm_so;
    memmove(result + pos + 1, result + pos + match.rm_eo - match.rm_so,
            strlen(result) - pos - match.rm_eo + match.rm_so + 1);
    offset = pos + 1;
  }
  regfree(&regex);
  return result;
}

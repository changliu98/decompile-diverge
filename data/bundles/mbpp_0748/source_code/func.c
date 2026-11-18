

#include <stdio.h>

#include <string.h>

#include <assert.h>

#include <regex.h>



void func0(const char *str1, char *result) {
  regex_t regex;
  regmatch_t matches[3];
  char buffer[1024];
  regcomp(&regex, "([a-z])([A-Z])", REG_EXTENDED);
  strcpy(buffer, str1);
  const char *cursor = buffer;
  result[0] = '\0';
  while (regexec(&regex, cursor, 3, matches, 0) == 0) {
    strncat(result, cursor, matches[1].rm_eo);
    strcat(result, " ");
    cursor += matches[2].rm_so;
  }
  strcat(result, cursor);
  regfree(&regex);
}

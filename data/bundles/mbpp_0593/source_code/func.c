

#include <stdio.h>

#include <assert.h>

#include <stdlib.h>

#include <string.h>

#include <regex.h>



char* func0(const char* ip) {
  regex_t regex;
  regmatch_t matches[1];
  char pattern[] = "\\.0+";
  char* result = (char*)malloc(strlen(ip) + 1);
  char* current_location;
  regcomp(&regex, pattern, REG_EXTENDED);
  strcpy(result, ip);
  current_location = result;
  while (regexec(&regex, current_location, 1, matches, 0) == 0) {
    size_t len = strlen(current_location);
    size_t start = matches[0].rm_so;
    size_t end = matches[0].rm_eo;
    memmove(current_location + start + 1, current_location + end,
            len - end + 1);
    current_location += start + 1;
  }
  regfree(&regex);
  return result;
}

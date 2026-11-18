

#include <stdio.h>

#include <regex.h>

#include <assert.h>



char* func0(const char* text) {
  regex_t regex;
  int result;
  char* match_result;
  char* pattern = "ab{2,3}";
  regcomp(&regex, pattern, REG_EXTENDED);
  result = regexec(&regex, text, 0, NULL, 0);
  if (result == 0) {
    match_result = "Found a match!";
  } else {
    match_result = "Not matched!";
  }
  regfree(&regex);
  return match_result;
}

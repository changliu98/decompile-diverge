

#include <stdio.h>

#include <regex.h>

#include <assert.h>



char* func0(char* text) {
  regex_t regex;
  int result;
  char* pattern = "[A-Z]+[a-z]+$";
  regcomp(&regex, pattern, REG_EXTENDED);
  result = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (result == 0) {
    return "Yes";
  } else {
    return "No";
  }
}

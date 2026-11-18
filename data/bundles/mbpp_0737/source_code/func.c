

#include <stdio.h>

#include <assert.h>

#include <regex.h>



char* func0(char* string) {
  regex_t regex;
  int result;
  char* pattern = "^[aeiouAEIOU][A-Za-z0-9_]*";
  regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB);
  result = regexec(&regex, string, 0, NULL, 0);
  regfree(&regex);
  if (result == 0) {
    return "Valid";
  } else {
    return "Invalid";
  }
}

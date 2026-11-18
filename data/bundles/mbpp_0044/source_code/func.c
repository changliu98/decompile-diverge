#include <assert.h>

#include <regex.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>



char* func0(const char* text) {
  regex_t regex;
  int result;
  char* pattern = "^[[:alnum:]_]+";
  if (regcomp(&regex, pattern, REG_EXTENDED) != 0) {
    return "Regex compilation error";
  }
  result = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (result == 0) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}

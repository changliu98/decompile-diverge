#include <stdio.h>

#include <assert.h>

#include <string.h>

#include <regex.h>



char* func0(const char* text) {
  regex_t regex;
  char* patterns = "\\w+\\S*$";
  if (regcomp(&regex, patterns, REG_EXTENDED) == 0) {
    regmatch_t matches[1];
    if (regexec(&regex, text, 1, matches, 0) == 0) {
      regfree(&regex);
      return "Found a match!";
    } else {
      regfree(&regex);
      return "Not matched!";
    }
  }
  return "Regex compilation failed";
}

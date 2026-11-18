#include <string.h>

#include <stdio.h>

#include <assert.h>

#include <regex.h>



char *func0(const char *text) {
  regex_t regex;
  int regexInit;
  int regexSearch;
  char *patterns = "^[a-z]+_[a-z]+$";
  regexInit = regcomp(&regex, patterns, REG_EXTENDED);
  if (regexInit) {
    fprintf(stderr, "Could not compile regex\n");
    return ("Compilation error");
  }
  regexSearch = regexec(&regex, text, 0, NULL, 0);
  if (!regexSearch) {
    regfree(&regex);
    return ("Found a match!");
  } else if (regexSearch == REG_NOMATCH) {
    regfree(&regex);
    return ("Not matched!");
  } else {
    char errorMessage[100];
    regerror(regexSearch, &regex, errorMessage, sizeof(errorMessage));
    fprintf(stderr, "Regex match failed: %s\n", errorMessage);
    regfree(&regex);
    return ("Error occurred");
  }
}

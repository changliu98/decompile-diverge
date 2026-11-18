

#include <stdio.h>

#include <assert.h>

#include <regex.h>

#include <string.h>



char* func0(char* text) {
  regex_t regex;
  int reti;
  char* patterns = "[A-Z]+[a-z]+$";
  regcomp(&regex, patterns, REG_EXTENDED);
  reti = regexec(&regex, text, 0, NULL, 0);
  if (!reti) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}

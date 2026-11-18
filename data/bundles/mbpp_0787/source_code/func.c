

#include <stdio.h>

#include <assert.h>

#include <regex.h>

#include <string.h>



char* func0(const char* text) {
  regex_t regex;
  int reti;
  char* patterns = "ab{3}";
  reti = regcomp(&regex, patterns, REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  reti = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (!reti)
    return "Found a match!";
  else
    return "Not matched!";
}

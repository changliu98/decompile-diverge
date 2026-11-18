

#include <stdio.h>

#include <regex.h>

#include <assert.h>

#include <string.h>

char* func0(const char* text) {
  regex_t regex;
  char* pattern = "\\Bz\\B";
  int reti;
  reti = regcomp(&regex, pattern, REG_EXTENDED);
  if (reti) {
    fprintf(stderr, "Could not compile regex\n");
    return "Regex compilation error";
  }
  reti = regexec(&regex, text, 0, NULL, 0);
  if (!reti) {
    return "Found a match!";
  } else if (reti == REG_NOMATCH) {
    return "Not matched!";
  } else {
    char msgbuf[100];
    regerror(reti, &regex, msgbuf, sizeof(msgbuf));
    fprintf(stderr, "Regex match failed: %s\n", msgbuf);
    return "Regex execution error";
  }
  regfree(&regex);
}



#include <stdio.h>

#include <string.h>

#include <regex.h>

#include <assert.h>



const char* func0(const char* text) {
  regex_t regex;
  int ret;
  const char* patterns = "ab*?";
  ret = regcomp(&regex, patterns, REG_EXTENDED);
  if (ret) {
    return "Regex compilation failed";
  }
  ret = regexec(&regex, text, 0, NULL, 0);
  regfree(&regex);
  if (!ret) {
    return "Found a match!";
  } else {
    return "Not matched!";
  }
}

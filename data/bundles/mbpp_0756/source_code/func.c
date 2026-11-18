

#include <stdio.h>

#include <string.h>

#include <regex.h>

#include <assert.h>



const char* func0(const char* text) {
  regex_t regex;
  int ret;
  const char* result;
  ret = regcomp(&regex, "ab?", REG_EXTENDED);
  if (ret) {
    return "Not matched!";
  }
  ret = regexec(&regex, text, 0, NULL, 0);
  if (!ret) {
    result = "Found a match!";
  }
  else {
    result = "Not matched!";
  }
  regfree(&regex);
  return result;
}

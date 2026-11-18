

#include <stdio.h>

#include <assert.h>

#include <string.h>

#include <regex.h>



char* func0(const char* text) {
  regex_t regex;
  regmatch_t match[1];
  static char result[100];
  if (regcomp(&regex, "\\w+ly", REG_EXTENDED) != 0) {
    printf("Could not compile regex\n");
    return NULL;
  }
  if (regexec(&regex, text, 1, match, 0) == 0) {
    int start = match[0].rm_so;
    int end = match[0].rm_eo;
    char word[100];
    strncpy(word, text + start, end - start);
    word[end - start] = '\0';
    snprintf(result, sizeof(result), "%d-%d: %s", start, end, word);
    regfree(&regex);
    return result;
  }
  regfree(&regex);
  return NULL;
}

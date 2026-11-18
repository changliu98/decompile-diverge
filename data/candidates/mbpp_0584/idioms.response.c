char *func0(char *text)
{
  char *textp = text;
  int i;
  int match_count;
  struct regmatch_t match[1];
  struct regex_t regex;
  if (regcomp(&regex, "\\w+ly", 1)) {
    printf("Could not compile regex\n");
    return ((void *)0);
  }
  if (regexec(&regex, textp, 1, match, 0)) {
    regfree(&regex);
    return ((void *)0);
  }
  i = match[0].rm_so;
  int j = match[0].rm_eo;
  char word[100];
  strncpy(word, textp + i, j - i);
  word[j - i] = '\0';
  snprintf(get_ly_result, sizeof(get_ly_result), "%d-%d: %s", i, j, word);
  regfree(&regex);
  return get_ly_result;
}
char *func0(const char *text, int n) {
  regex_t regex;
  regmatch_t pmatch[1];
  static char new_text[256];
  strcpy(new_text, text);
  const char *pattern = "[ ,.]";
  regcomp(&regex, pattern, REG_EXTENDED);
  int num_replacements = 0;
  while (num_replacements < n && regexec(&regex, new_text, 1, pmatch, 0) == 0) {
    int start = pmatch[0].rm_so;
    new_text[start] = ':';
    num_replacements++;
  }
  regfree(&regex);
  return new_text;
}
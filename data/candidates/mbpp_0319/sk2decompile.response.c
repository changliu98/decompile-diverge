char **func0(char *str, int *count) {
  char regex[] = "\\b[a-zA-Z]{5}\\b";
  regex_t preg;
  int c = 0;
  char str2[strlen(str) + 1];
  strcpy(str2, str);
  regcomp(&preg, regex, 1);
  char *p = str2;
  regmatch_t pmatch[1];
  while (regexec(&preg, p, 1, pmatch, 0) == 0) {
    int start = pmatch[0].rm_so;
    int end = pmatch[0].rm_eo;
    char *s = malloc(end - start + 1);
    strncpy(s, p + start, end - start);
    s[end - start] = '\0';
    words[c++] = s;
    p += end;
  }
  regfree(&preg);
  *count = c;
  return words;
}
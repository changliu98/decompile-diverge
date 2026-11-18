void __camel_to_words(char *camel, char *words) {
  regex_t preg;
  char buf[1024];
  regmatch_t pmatch[3];
  char *p;
  regcomp(&preg, "([a-z])([A-Z])", 1);
  strcpy(buf, camel);
  p = buf;
  words[0] = '\0';
  while (!regexec(&preg, p, 3, pmatch, 0)) {
    strncat(words, p, pmatch[1].rm_eo);
    strcat(words, " ");
    p += pmatch[2].rm_eo;
  }
  strcat(words, p);
  regfree(&preg);
}
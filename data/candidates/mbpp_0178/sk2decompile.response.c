char *_regex_match(char **regex_list, int regex_list_size, char *str) {
  int i;
  regex_t regex;
  for (i = 0; i < regex_list_size; i++) {
    int reti = regcomp(&regex, regex_list[i], 0);
    if (reti) {
      fprintf(stderr, "Could not compile regex\n");
      return "Not Matched!";
    }
    reti = regexec(&regex, str, 0, NULL, 0);
    if (!reti) {
      regfree(&regex);
      return "Matched!";
    }
    regfree(&regex);
  }
  return "Not Matched!";
}
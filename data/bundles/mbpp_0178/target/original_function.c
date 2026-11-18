char* func0(char* patterns[], int pattern_n, char* text) {
  regex_t regex;
  int reti;
  for (int i = 0; i < pattern_n; i++) {
    reti = regcomp(&regex, patterns[i], 0);
    if (reti) {
      fprintf(stderr, "Could not compile regex\n");
      return "Not Matched!";
    }
    reti = regexec(&regex, text, 0, NULL, 0);
    if (!reti) {
      regfree(&regex);
      return "Matched!";
    }
    regfree(&regex);
  }
  return "Not Matched!";
}
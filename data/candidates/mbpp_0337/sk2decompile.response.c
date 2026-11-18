char *func0(char *str) {
  regex_t preg;
  char *pattern = "\\w+\\S*$";
  int reti;
  regmatch_t pmatch[1];
  reti = regcomp(&preg, pattern, 1);
  if (reti) {
    return "Regex compilation failed";
  }
  reti = regexec(&preg, str, 1, pmatch, 0);
  if (!reti) {
    regfree(&preg);
    return "Found a match!";
  } else {
    regfree(&preg);
    return "Not matched!";
  }
}
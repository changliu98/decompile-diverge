char *func0(char *s) {
  regex_t re;
  int reti;
  reti = regcomp(&re, "ab*?", 1);
  if (reti) return "Regex compilation failed";
  reti = regexec(&re, s, 0, NULL, 0);
  regfree(&re);
  if (reti) return "Not matched!";
  return "Found a match!";
}
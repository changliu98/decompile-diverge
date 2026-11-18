char *func0(char *s) {
  int len = strlen(s);
  if (len > 4 && !strcmp(s + len - 4, "Road")) {
    s[len - 4] = '\0';
    strcat(s, "Rd.");
  }
  return s;
}
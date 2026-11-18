int func0(char *s) {
  int i, len, count = 0;
  len = strlen(s);
  for (i = 1; i < len - 1; i++) {
    if (strchr("aeiou", s[i]) == NULL &&
        (strchr("aeiou", s[i - 1]) != NULL ||
         strchr("aeiou", s[i + 1]) != NULL)) {
      count++;
    }
  }
  if (strchr("aeiou", s[0]) == NULL && strchr("aeiou", s[1]) != NULL) {
    count++;
  }
  if (strchr("aeiou", s[len - 1]) == NULL &&
      strchr("aeiou", s[len - 2]) != NULL) {
    count++;
  }
  return count;
}
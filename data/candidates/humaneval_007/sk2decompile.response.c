char **_get_matching_strings(char **strings, int nstrings, char *match,
                             int *nmatch) {
  char **matching = NULL;
  int i, n = 0;
  for (i = 0; i < nstrings; i++) {
    if (strstr(strings[i], match)) {
      matching = realloc(matching, (n + 1) * sizeof(char *));
      matching[n] = strings[i];
      n++;
    }
  }
  *nmatch = n;
  return matching;
}
char *func0(char **strings, int n) {
  char **strs = strings;
  int nstrs = n;
  char *longest = "";
  int longest_len = 0;
  for (int i = 0; i < nstrs; i++) {
    char unique[256];
    memset(unique, 0, 256);
    int len = 0;
    for (int j = 0; strs[i][j] != '\0'; j++) {
      if (strchr(unique, strs[i][j]) == NULL) {
        int ulen = strlen(unique);
        unique[ulen] = strs[i][j];
        unique[ulen + 1] = '\0';
        len++;
      }
    }
    if (len > longest_len ||
        (len == longest_len && strcmp(strs[i], longest) < 0)) {
      longest = strs[i];
      longest_len = len;
    }
  }
  return longest;
}
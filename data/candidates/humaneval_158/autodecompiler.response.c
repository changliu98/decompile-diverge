char *func0(char **strings, int n) {
  char *best = "";
  int best_n = 0;
  for (int i = 0; i < n; i++) {
    char unique[256];
    memset(unique, 0, sizeof(unique));
    int n_unique = 0;
    for (int j = 0; strings[i][j]; j++) {
      if (strchr(unique, strings[i][j]) == NULL) {
        int l = strlen(unique);
        unique[l] = strings[i][j];
        unique[l + 1] = '\0';
        n_unique++;
      }
    }
    if (n_unique > best_n || (n_unique == best_n && strcmp(strings[i], best) < 0)) {
      best = strings[i];
      best_n = n_unique;
    }
  }
  return best;
}
int linenoiseHistorySetMaxLen(int len) {
  if (len < 1) return 0;
  if (history) {
    int old_len = history_len;
    char **new_history = malloc(sizeof(char *) * len);
    if (!new_history) return 0;
    if (len < old_len) {
      int i;
      for (i = 0; i < old_len - len; i++) free(history[i]);
      old_len = len;
    }
    memset(new_history, 0, sizeof(char *) * len);
    memcpy(new_history, history + (history_len - old_len),
           sizeof(char *) * old_len);
    free(history);
    history = new_history;
  }
  history_max_len = len;
  if (history_len > history_max_len) history_len = history_max_len;
  return 1;
}
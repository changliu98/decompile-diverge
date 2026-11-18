int linenoiseHistorySetMaxLen(int len)

{
  int iVar1;
  char **__s;
  int j;
  int tocopy;
  char **new;
  int len_local;
  int local_c;
  
  iVar1 = history_len;
  if (len < 1) {
    local_c = 0;
  }
  else {
    if (history != (char **)0x0) {
      tocopy = history_len;
      __s = malloc((long)len << 3);
      if (__s == (char **)0x0) {
        return 0;
      }
      if (len < iVar1) {
        for (j = 0; tocopy = len, j < iVar1 - len; j = j + 1) {
          free(history[j]);
        }
      }
      memset(__s,0,(long)len << 3);
      memcpy(__s,history + (history_len - tocopy),(long)tocopy << 3);
      free(history);
      history = __s;
    }
    if (len < history_len) {
      history_len = len;
    }
    local_c = 1;
    history_max_len = len;
  }
  return local_c;
}
int rl_set_history_max_len(int len)
{
 int ret;

 if (len < 2) {
  ret = 0;
 } else if (history) {
  int i, n = history_len;
  char **new;

  new = malloc(len * sizeof(char *));
  if (!new) {
   ret = 0;
  } else {
   if (len < n) {
    for (i = 0; i < n - len; i++)
     free(history[i]);
    n = len;
   }
   memset(new, 0, len * sizeof(char *));
   memcpy(new, history + history_len - n, n * sizeof(char *));
   free(history);
   history = new;
  }
 }

 if (ret)
  history_max_len = len;
 else
  history_max_len = 100;

 if (history_len > history_max_len)
  history_len = history_max_len;

 return ret;
}
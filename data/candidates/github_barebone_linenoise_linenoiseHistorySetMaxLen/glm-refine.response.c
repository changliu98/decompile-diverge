int __cdecl linenoiseHistorySetMaxLen(int len)
{
  int tocopy;
  char **new_history;

  // Disallow non-positive lengths
  if (len < 1)
    return 0;

  if (history) 
  {
    tocopy = history_len;
    
    // Allocate new array for the history
    new_history = (char **)malloc(sizeof(char *) * len);
    if (!new_history)
      return 0;

    // If the new max length is smaller than the current history, 
    // we must free the oldest entries that won't fit.
    if (len < tocopy) 
    {
      for (int j = 0; j < tocopy - len; ++j)
        free(history[j]);
      tocopy = len;
    }

    // Copy the most recent entries to the new array
    memcpy(new_history, &history[history_len - tocopy], sizeof(char *) * tocopy);
    
    // Free the old history array and update the pointer
    free(history);
    history = new_history;
  }
  
  history_max_len = len;
  
  // Truncate history_len if it exceeds the new max length
  if (history_len > len)
    history_len = history_max_len;
    
  return 1;
}
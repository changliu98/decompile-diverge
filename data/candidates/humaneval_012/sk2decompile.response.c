char *_get_longest_string(char **strings, int num_strings) {
  char *longest = "";
  int longest_len = 0;
  int i;
  int len;
  for (i = 0; i < num_strings; i++) {
    len = strlen(strings[i]);
    if (len > longest_len) {
      longest = strings[i];
      longest_len = len;
    }
  }
  return longest;
}
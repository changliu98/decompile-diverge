char func0(char *str) {
  int size = 256;
  int count[256];
  memset(count, 0, sizeof(count));
  int max = -1;
  char result = '\0';
  int len = strlen(str);
  int i;
  for (i = 0; i < len; i++) count[str[i]]++;
  for (i = 0; i < len; i++) {
    if (count[str[i]] > max) {
      max = count[str[i]];
      result = str[i];
    }
  }
  return result;
}
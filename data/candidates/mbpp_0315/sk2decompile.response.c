char *func0(char *s) {
  static char result[100];
  int len = strlen(s);
  int i = 0;
  int count = 0;
  int max_count = 0;
  int max_index = -1;
  while (i < len) {
    if (s[i] == ' ') {
      if (count % 2 == 0 && max_count < count) {
        max_count = count;
        max_index = i - count;
      }
      count = 0;
    } else {
      count++;
    }
    i++;
  }
  if (count % 2 == 0 && max_count < count) {
    max_count = count;
    max_index = i - count;
  }
  if (max_index == -1) {
    return "";
  }
  strncpy(result, s + max_index, max_count);
  result[max_count] = '\0';
  return result;
}
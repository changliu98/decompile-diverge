char* func0(char* s, char c) {
  int counts = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] == c) {
      counts++;
    }
  }
  char* result = (char*)malloc(strlen(s) - counts + 1);
  int j = 0;
  for (int i = 0; s[i] != '\0'; i++) {
    if (s[i] != c) {
      result[j] = s[i];
      j++;
    }
  }
  result[j] = '\0';
  return result;
}
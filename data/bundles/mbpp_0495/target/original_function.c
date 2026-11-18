char* func0(const char* str1) {
  static char result[100];
  int i, j = 0;
  for (i = 0; str1[i] != '\0'; i++) {
    if (str1[i] < 'a' || str1[i] > 'z') {
      result[j++] = str1[i];
    }
  }
  result[j] = '\0';
  return result;
}
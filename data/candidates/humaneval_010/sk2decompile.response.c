char *func0(const char *s) {
  int len = strlen(s);
  char *result = malloc(2 * len + 1);
  if (result == NULL) {
    return NULL;
  }
  for (int i = 0; i < len; i++) {
    int is_palindrome = 1;
    for (int j = 0; j < (len - i) / 2; j++) {
      if (s[i + j] != s[len - 1 - j]) {
        is_palindrome = 0;
        break;
      }
    }
    if (is_palindrome) {
      strncpy(result, s, len);
      for (int j = 0; j < i; j++) {
        result[len + j] = s[i - j - 1];
      }
      result[len + i] = '\0';
      return result;
    }
  }
  strncpy(result, s, len);
  for (int j = 0; j < len; j++) {
    result[len + j] = s[len - j - 1];
  }
  result[2 * len] = '\0';
  return result;
}
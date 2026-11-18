char* func0(const char* S) {
  static char result[100];
  int j = 0;
  for (int i = 0; i < strlen(S); i++) {
    if (isalnum(S[i])) {
      result[j++] = S[i];
    }
  }
  result[j] = '\0';
  return result;
}
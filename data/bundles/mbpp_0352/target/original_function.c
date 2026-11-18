bool func0(const char* str) {
  for (int i = 0; i < strlen(str); i++) {
    for (int j = i + 1; j < strlen(str); j++) {
      if (str[i] == str[j]) {
        return false;
      }
    }
  }
  return true;
}
char* func0(const char* str) {
  int len = strlen(str);
  if (str[0] == str[len - 1]) {
    return "Equal";
  } else {
    return "Not Equal";
  }
}
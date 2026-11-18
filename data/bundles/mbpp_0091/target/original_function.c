bool func0(char *str1[], char *sub_str, int size) {
  for (int i = 0; i < size; i++) {
    if (strstr(str1[i], sub_str) != NULL) {
      return true;
    }
  }
  return false;
}
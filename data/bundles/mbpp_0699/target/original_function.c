int func0(const char* str1, const char* str2) {
  int count = 0;
  int length = strlen(str1);
  for (int i = 0; i < length; i++) {
    if (str1[i] != str2[i]) {
      count++;
    }
  }
  if (count % 2 == 0) {
    return (count / 2);
  } else {
    return -1;
  }
}
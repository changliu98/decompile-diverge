char func0(const char* str1) {
  int ASCII_SIZE = 256;
  int ctr[256] = {0};
  int max = -1;
  char ch = '\0';
  int length = strlen(str1);
  for (int i = 0; i < length; i++) {
    ctr[(int)str1[i]]++;
  }
  for (int i = 0; i < length; i++) {
    if (max < ctr[(int)str1[i]]) {
      max = ctr[(int)str1[i]];
      ch = str1[i];
    }
  }
  return ch;
}
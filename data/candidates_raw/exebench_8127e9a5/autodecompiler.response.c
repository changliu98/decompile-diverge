void reverse(char *s) {
  size_t len;
  size_t i;
  for (len = 0; ; len++) {
    if (s[len] == '\0') {
      break;
    }
  }

  if (len > 0) {
    size_t start = 0;
    size_t end = len - 1;

    while (1) {
      if (start >= end) {
        break;
      }

      char temp = s[start];
      s[start] = s[end];
      s[end] = temp;

      start++;
      end--;
    }
  }
}
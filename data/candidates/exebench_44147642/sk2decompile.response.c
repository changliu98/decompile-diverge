void uppercase(int *c) {
  int ch = *c;
  if ((ch >= 97 && ch <= 105) || (ch >= 106 && ch <= 114) ||
      (ch >= 115 && ch <= 122)) {
    *c = ch - 32;
  }
}
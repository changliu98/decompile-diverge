void uc(char *s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z') *s -= 32;
    s++;
  }
}
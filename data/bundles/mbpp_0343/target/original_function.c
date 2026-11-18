void func0(const char *s, int *letters, int *digits) {
  int l = 0, d = 0;
  while (*s) {
    if (isdigit((unsigned char)*s))
      d++;
    else if (isalpha((unsigned char)*s))
      l++;
    s++;
  }
  *letters = l;
  *digits = d;
}
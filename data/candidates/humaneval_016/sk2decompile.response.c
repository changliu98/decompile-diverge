int _str_count_unique_letters(const char *str) {
  int letters[256];
  int i, count;
  char c;
  const char *s;
  s = str;
  count = 0;
  memset(letters, 0, sizeof(letters));
  for (i = 0; s[i]; i++) {
    c = tolower((unsigned char)s[i]);
    if (letters[c] == 0 && isalpha((unsigned char)c)) {
      letters[c] = 1;
      count++;
    }
  }
  return count;
}
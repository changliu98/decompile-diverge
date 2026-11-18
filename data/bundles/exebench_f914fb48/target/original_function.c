void strupper(char s[]) {
  int i;

  for (i = 0; s[i] != '\0'; i++) {
    if ('a' <= s[i] && s[i] <= 'z')
      s[i] += 'A' - 'a';
  }
}
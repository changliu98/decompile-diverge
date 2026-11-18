char *func0(char *s) {
  int i, len, count = 0;
  char temp;
  len = strlen(s);
  for (i = 0; i < len; i++) {
    if (!isalpha((unsigned char)s[i])) {
      count++;
    } else if (islower((unsigned char)s[i])) {
      s[i] = tolower((unsigned char)s[i]);
    } else if (isupper((unsigned char)s[i])) {
      s[i] = toupper((unsigned char)s[i]);
    }
  }
  if (count == len) {
    for (i = 0; i < len / 2; i++) {
      temp = s[i];
      s[i] = s[len - i - 1];
      s[len - i - 1] = temp;
    }
  }
  return s;
}
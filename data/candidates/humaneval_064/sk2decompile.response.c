int _count_vowels(char *str) {
  int i, len, count = 0;
  len = strlen(str);
  for (i = 0; i < len; i++) {
    if (strchr("aeiouAEIOU", str[i])) count++;
  }
  if (len > 0 && (str[len - 1] == 'y' || str[len - 1] == 'Y')) count++;
  return count;
}
int c_insensitive(char *s1, char *s2) {
  int i;
  for (i = 0; s1[i]; i++)
    if (s1[i] >= 'a' && s1[i] <= 'z') s1[i] -= 32;
  for (i = 0; s2[i]; i++)
    if (s2[i] >= 'a' && s2[i] <= 'z') s2[i] -= 32;
  for (i = 0; s1[i] && s2[i]; i++) {
    if (s1[i] > s2[i]) return 1;
    if (s1[i] < s2[i]) return -1;
  }
  return 0;
}
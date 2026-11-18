bool _is_anagram(char *s1, char *s2) {
  int len1 = strlen(s1);
  int len2 = strlen(s2);
  int i, j;
  bool found;
  for (i = 0; i < len1; i++) {
    found = false;
    for (j = 0; j < len2; j++) {
      if (s1[i] == s2[j]) {
        found = true;
        break;
      }
    }
    if (!found) return false;
  }
  for (i = 0; i < len2; i++) {
    found = false;
    for (j = 0; j < len1; j++) {
      if (s2[i] == s1[j]) {
        found = true;
        break;
      }
    }
    if (!found) return false;
  }
  return true;
}
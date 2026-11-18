int minDeletions(char* s) {
  int max = 0;
  int len = strlen(s);
  int count[26];
  int i;
  memset(count, 0, sizeof(count));
  for (i = 0; i < len; i++) {
    count[s[i] - 'a']++;
  }
  for (i = 0; i < 26; i++) {
    if (count[i] > max) {
      max = count[i];
    }
  }
  return len - max;
}
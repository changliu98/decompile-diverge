int _check_key(char ***key, int key_size) {
  if (key_size == 0) return 0;
  int i, j;
  int upper = 0;
  int lower = 0;
  for (i = 0; i < key_size; i++) {
    char *word = (*key)[i * 2];
    for (j = 0; word[j] != '\0'; j++) {
      if (!isalpha(word[j])) return 0;
      if (isupper(word[j])) upper = 1;
      if (islower(word[j])) lower = 1;
      if (upper + lower == 2) return 0;
    }
  }
  return 1;
}
int _filter(char **array, int size, char *prefix, char ***out) {
  int prefix_len = strlen(prefix);
  *out = malloc(size * sizeof(char *));
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (!strncmp(array[i], prefix, prefix_len)) {
      (*out)[count++] = array[i];
    }
  }
  return count;
}
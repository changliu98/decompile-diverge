int _get_min_int(char **argv, int argc) {
  int i, j, min = INT_MAX;
  for (i = 0; i < argc; i++) {
    if (sscanf(argv[i], "%d", &j)) {
      if (j < min) {
        min = j;
      }
    }
  }
  return min;
}
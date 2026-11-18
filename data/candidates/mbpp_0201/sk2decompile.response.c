int _is_unique(char **argv, int argc) {
  int i;
  for (i = 1; i < argc; i++) {
    if (!(!strcmp(argv[0], argv[i]))) return 0;
  }
  return 1;
}
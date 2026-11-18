int func0(char *lst[], int size) {
  for (int i = 1; i < size; i++) {
    if (strcmp(lst[0], lst[i]) != 0) {
      return 0;
    }
  }
  return 1;
}
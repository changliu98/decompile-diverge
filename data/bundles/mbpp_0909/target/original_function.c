int func0(int num) {
  char num_str[12], rev_str[12];
  for (int x = num - 1; x > 0; x--) {
    sprintf(num_str, "%d", x);
    strcpy(rev_str, num_str);
    int len = strlen(rev_str);
    char temp;
    for (int i = 0; i < len / 2; i++) {
      temp = rev_str[i];
      rev_str[i] = rev_str[len - 1 - i];
      rev_str[len - 1 - i] = temp;
    }
    if (strcmp(num_str, rev_str) == 0) {
      return x;
    }
  }
  return 0;
}
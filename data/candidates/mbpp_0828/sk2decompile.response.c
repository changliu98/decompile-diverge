void func0(char *str, int *alpha, int *digit, int *other) {
  int i;
  *other = *digit = *alpha = 0;
  for (i = 0; str[i] != '\0'; i++) {
    if (isalpha(str[i]))
      (*alpha)++;
    else if (isdigit(str[i]))
      (*digit)++;
    else
      (*other)++;
  }
}
void _count_alpha_digit(const char *str, int *alpha, int *digit) {
  int a = 0;
  int d = 0;
  for (; *str != '\0'; str++) {
    if (isdigit((unsigned char)*str))
      d++;
    else if (isalpha((unsigned char)*str))
      a++;
  }
  *alpha = a;
  *digit = d;
}
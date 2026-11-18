char* func0(int a, int b, int c, int d) {
  int total = 0;
  if (a > 0) total += a;
  if (b > 0) total += b;
  if (c > 0) total += c;
  if (d > 0) total += d;
  char* result = malloc((total + 1) * sizeof(char));
  if (!result) {
    perror("Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  int index = 0;
  for (int i = 0; i < a; i++) {
    result[index++] = 'p';
  }
  for (int i = 0; i < b; i++) {
    result[index++] = 'q';
  }
  for (int i = 0; i < c; i++) {
    result[index++] = 'r';
  }
  for (int i = 0; i < d; i++) {
    result[index++] = 's';
  }
  result[index] = '\0';
  return result;
}
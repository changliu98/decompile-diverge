char *func0(char *a, char *b) {
  char *a_copy = strdup(a);
  char *b_copy = strdup(b);
  int i;
  for (i = 0; a_copy[i] != '\0'; i++) {
    if (a_copy[i] == ',') {
      a_copy[i] = '.';
    }
  }
  for (i = 0; b_copy[i] != '\0'; i++) {
    if (b_copy[i] == ',') {
      b_copy[i] = '.';
    }
  }
  double a_double, b_double;
  char *endptr;
  a_double = strtod(a_copy, &endptr);
  if (*endptr != '\0') {
    free(a_copy);
    free(b_copy);
    return "Invalid input";
  }
  b_double = strtod(b_copy, &endptr);
  if (*endptr != '\0') {
    free(a_copy);
    free(b_copy);
    return "Invalid input";
  }
  free(a_copy);
  free(b_copy);
  if (a_double == b_double) {
    return "None";
  } else if (a_double > b_double) {
    return a;
  } else {
    return b;
  }
}
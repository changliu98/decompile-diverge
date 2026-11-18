char pop(char stack[], int *top) {
  char c = -1;
  if (*top >= 0 && *top < 100) {
    c = stack[*top];
    *top = *top - 1;
  }
  return c;
}
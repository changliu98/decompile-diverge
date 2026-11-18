double push(double *stack, int *pointer, double value)
{
  if (*pointer < 16)
    stack[(*pointer)++] = value;
  return value;
}
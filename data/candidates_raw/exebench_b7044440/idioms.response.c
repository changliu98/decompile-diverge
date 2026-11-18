void pop(int *stack)
{
  int i;
  for (i = 0; i < 9; i++)
    stack[i] = stack[i + 1];
  stack[9] = -1;
}
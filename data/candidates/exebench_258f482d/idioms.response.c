void iadd(int *stack, int *spointer, int operand)
{
  int value1 = stack[*spointer];
  --(*spointer);
  stack[*spointer] += value1;
}
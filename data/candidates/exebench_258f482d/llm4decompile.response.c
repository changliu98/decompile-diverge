void iadd(int *stack, int *spointer, int operand)
{
  int value = stack[*spointer];
  *spointer -= 1;
  stack[*spointer] += value;
}
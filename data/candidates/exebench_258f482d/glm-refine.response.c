void __cdecl iadd(int *stack, int *spointer, int operand)
{
  // Pop the top value from the stack
  int value1 = stack[*spointer];
  *spointer -= 1;

  // Add the popped value to the new top of the stack
  stack[*spointer] += value1;
}
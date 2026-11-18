void __cdecl iadd(int *stack, int *spointer, int operand)
{
  int value1; // [rsp+4h] [rbp-18h]

  value1 = stack[(*spointer)--];
  stack[*spointer] += value1;
}
void iadd(int *stack,int *spointer,int operand)

{
  int iVar1;
  int value2;
  int value1;
  int operand_local;
  int *spointer_local;
  int *stack_local;
  
  iVar1 = stack[*spointer];
  *spointer = *spointer + -1;
  stack[*spointer] = iVar1 + stack[*spointer];
  return;
}
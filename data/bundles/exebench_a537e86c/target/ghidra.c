double dst_transform_push(double *stack,int *pointer,double value)

{
  int iVar1;
  double value_local;
  int *pointer_local;
  double *stack_local;
  
  if (*pointer < 0x10) {
    iVar1 = *pointer;
    *pointer = iVar1 + 1;
    stack[iVar1] = value;
  }
  return value;
}
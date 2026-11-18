uchar pop(uchar *stack,int *position)

{
  uchar result;
  int *position_local;
  uchar *stack_local;
  
  result = 0xff;
  if ((*position < 100) && (-1 < *position)) {
    result = stack[*position];
    *position = *position + -1;
  }
  return result;
}
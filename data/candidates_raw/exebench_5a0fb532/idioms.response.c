char pop(char *stack, int *position)
{
  char poped = -1;
  if ( *position < (sizeof(stack)/sizeof(char)) )
  {
    poped = stack[*position];
    (*position)--;
  }
  return poped;
}
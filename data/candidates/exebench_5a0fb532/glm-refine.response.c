unsigned __int8 __cdecl pop(unsigned __int8 *stack, int *position)
{
  if ((unsigned int)*position <= 0x63)
    return stack[(*position)--];
  return -1;
}
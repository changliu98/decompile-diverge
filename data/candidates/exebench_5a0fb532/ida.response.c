unsigned __int8 __cdecl pop(unsigned __int8 *stack, int *position)
{
  unsigned __int8 result; // [rsp+1h] [rbp-11h]

  result = -1;
  if ( (unsigned int)*position <= 0x63 )
    return stack[(*position)--];
  return result;
}
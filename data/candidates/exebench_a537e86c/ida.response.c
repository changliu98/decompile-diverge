double __cdecl dst_transform_push(double *stack, int *pointer, double value)
{
  int v3; // ecx

  if ( *pointer < 16 )
  {
    v3 = (*pointer)++;
    stack[v3] = value;
  }
  return value;
}
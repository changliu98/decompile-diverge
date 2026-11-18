bool __cdecl func0(float *l, int size)
{
  int i; // [rsp+0h] [rbp-20h]
  int decr; // [rsp+4h] [rbp-1Ch]
  int incr; // [rsp+8h] [rbp-18h]

  decr = 0;
  incr = 0;
  for ( i = 1; i < size; ++i )
  {
    if ( l[i] > l[i - 1] )
      incr = 1;
    if ( l[i - 1] > l[i] )
      decr = 1;
  }
  return decr + incr != 2;
}
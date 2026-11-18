void __cdecl set_mask(int *mask, int size, int offset, int length)
{
  int i; // [rsp+0h] [rbp-18h]

  i = 0;
  if ( offset > 0 )
  {
    i = 1;
    *mask = -offset;
  }
  mask[i] = length;
  mask[i + 1] = length - (size - offset);
  mask[i + 2] = 0;
}
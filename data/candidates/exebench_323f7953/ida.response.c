void __cdecl increasingArray(int *array)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < 16; ++i )
    array[i] = i;
}
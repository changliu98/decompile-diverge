void __cdecl getNums(int *numbers)
{
  int i; // [rsp+0h] [rbp-Ch]

  for ( i = 0; i < 4; ++i )
    numbers[i] = 2 * i;
}
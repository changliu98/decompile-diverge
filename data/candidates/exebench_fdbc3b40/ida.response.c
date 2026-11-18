void __cdecl multiply_all(int *arr, int num)
{
  int i; // [rsp+0h] [rbp-10h]

  for ( i = 0; i < 10; ++i )
    arr[i] *= num;
}
int __cdecl int2arr(int *arr, int num)
{
  int i; // [rsp+0h] [rbp-10h]

  i = 0;
  while ( num )
  {
    arr[i] = num % 10;
    num /= 10;
    ++i;
  }
  return i;
}
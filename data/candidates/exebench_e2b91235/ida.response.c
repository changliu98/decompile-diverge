int __cdecl num_to_array(int *arr, int num)
{
  int v2; // ecx
  int i; // [rsp+0h] [rbp-14h]

  i = 0;
  while ( num > 0 )
  {
    v2 = i++;
    arr[v2] = num % 10;
    num /= 10;
  }
  return i;
}
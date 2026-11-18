int __cdecl func0(int *arr, int lens, int n)
{
  int i; // [rsp+4h] [rbp-18h]
  int mul; // [rsp+8h] [rbp-14h]

  mul = 1;
  for ( i = 0; i < lens; ++i )
    mul = arr[i] % n * mul % n;
  return mul % n;
}
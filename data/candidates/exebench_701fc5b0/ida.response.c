int __cdecl foo(int *a)
{
  int v1; // edx
  int j; // [rsp+0h] [rbp-10h]
  int i; // [rsp+4h] [rbp-Ch]

  j = 0;
  for ( i = 0; i < 10; ++i )
  {
    v1 = j++;
    a[i] = v1;
  }
  return j + i;
}
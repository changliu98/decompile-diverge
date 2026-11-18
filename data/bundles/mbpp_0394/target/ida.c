bool __cdecl func0(int *test_tup, int size)
{
  int v2; // ecx
  __int64 v4; // [rsp+0h] [rbp-40h] BYREF
  int j; // [rsp+Ch] [rbp-34h]
  bool found; // [rsp+13h] [rbp-2Dh]
  int ele; // [rsp+14h] [rbp-2Ch]
  int i; // [rsp+18h] [rbp-28h]
  int temp_size; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  __int64 *v11; // [rsp+28h] [rbp-18h]
  bool res; // [rsp+33h] [rbp-Dh]
  int sizea; // [rsp+34h] [rbp-Ch]
  int *test_tupa; // [rsp+38h] [rbp-8h]

  test_tupa = test_tup;
  sizea = size;
  res = 1;
  v11 = &v4;
  v4 = (__int64)&v4 - ((4LL * (unsigned int)size + 15) & 0xFFFFFFFFFFFFFFF0LL);
  __vla_expr0 = (unsigned int)size;
  temp_size = 0;
  for ( i = 0; i < sizea; ++i )
  {
    ele = test_tupa[i];
    found = 0;
    for ( j = 0; j < temp_size; ++j )
    {
      if ( *(_DWORD *)(v4 + 4LL * j) == ele )
      {
        found = 1;
        break;
      }
    }
    if ( found )
      return 0;
    v2 = temp_size++;
    *(_DWORD *)(v4 + 4LL * v2) = ele;
  }
  return res;
}
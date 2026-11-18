int __cdecl func0(int *lst, int size)
{
  int v2; // edx
  int v3; // ecx
  _BYTE v5[7]; // [rsp+0h] [rbp-40h] BYREF
  bool v6; // [rsp+7h] [rbp-39h]
  void *base; // [rsp+8h] [rbp-38h]
  int i_0; // [rsp+10h] [rbp-30h]
  int sum; // [rsp+14h] [rbp-2Ch]
  int i; // [rsp+18h] [rbp-28h]
  int count; // [rsp+1Ch] [rbp-24h]
  unsigned __int64 __vla_expr0; // [rsp+20h] [rbp-20h]
  _BYTE *v13; // [rsp+28h] [rbp-18h]
  int sizea; // [rsp+34h] [rbp-Ch]
  int *lsta; // [rsp+38h] [rbp-8h]

  lsta = lst;
  sizea = size;
  v13 = v5;
  base = &v5[-((4LL * (unsigned int)size + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = (unsigned int)size;
  count = 0;
  for ( i = 0; i < sizea; ++i )
  {
    if ( lsta[i] > 0 )
    {
      v2 = lsta[i];
      v3 = count++;
      *((_DWORD *)base + v3) = v2;
    }
  }
  qsort(base, count, 4uLL, (__compar_fn_t)compare);
  sum = 0;
  for ( i_0 = 0; ; ++i_0 )
  {
    v6 = 0;
    if ( i_0 < 3 )
      v6 = i_0 < count;
    if ( !v6 )
      break;
    sum += *((_DWORD *)base + i_0);
  }
  return sum;
}
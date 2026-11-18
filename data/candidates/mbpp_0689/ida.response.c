int __cdecl func0(int *arr, int n)
{
  _BYTE v3[12]; // [rsp+0h] [rbp-50h] BYREF
  int v4; // [rsp+Ch] [rbp-44h]
  _DWORD *v5; // [rsp+10h] [rbp-40h]
  int j; // [rsp+1Ch] [rbp-34h]
  int i; // [rsp+20h] [rbp-30h]
  int v8; // [rsp+24h] [rbp-2Ch]
  unsigned __int64 __vla_expr0; // [rsp+28h] [rbp-28h]
  _BYTE *v10; // [rsp+30h] [rbp-20h]
  int na; // [rsp+3Ch] [rbp-14h]
  int *arra; // [rsp+40h] [rbp-10h]
  int v13; // [rsp+4Ch] [rbp-4h]

  arra = arr;
  na = n;
  v10 = v3;
  v5 = &v3[-((4LL * (unsigned int)n + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = (unsigned int)n;
  if ( n && *arra )
  {
    *v5 = 0;
    for ( i = 1; i < na; ++i )
    {
      v5[i] = 0x7FFFFFFF;
      for ( j = 0; j < i; ++j )
      {
        if ( i <= arra[j] + j && v5[j] != 0x7FFFFFFF )
        {
          if ( v5[i] >= v5[j] + 1 )
            v4 = v5[j] + 1;
          else
            v4 = v5[i];
          v5[i] = v4;
          break;
        }
      }
    }
    v13 = v5[na - 1];
    v8 = 1;
  }
  else
  {
    v13 = 0x7FFFFFFF;
    v8 = 1;
  }
  return v13;
}
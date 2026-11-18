char *__cdecl func0(int *seq_nums, int n)
{
  _DWORD *v3; // [rsp+0h] [rbp-40h] BYREF
  int v4; // [rsp+Ch] [rbp-34h]
  int i; // [rsp+10h] [rbp-30h]
  int x; // [rsp+14h] [rbp-2Ch]
  unsigned __int64 __vla_expr0; // [rsp+18h] [rbp-28h]
  _DWORD **v8; // [rsp+20h] [rbp-20h]
  int na; // [rsp+2Ch] [rbp-14h]
  int *seq_numsa; // [rsp+30h] [rbp-10h]
  char *v11; // [rsp+38h] [rbp-8h]

  seq_numsa = seq_nums;
  na = n;
  v8 = &v3;
  v3 = (_DWORD *)((char *)&v3 - ((4LL * (unsigned int)(n - 1) + 15) & 0xFFFFFFFFFFFFFFF0LL));
  __vla_expr0 = (unsigned int)(n - 1);
  for ( x = 1; x < na; ++x )
    v3[x - 1] = seq_numsa[x] - seq_numsa[x - 1];
  for ( i = 1; i < na - 1; ++i )
  {
    if ( v3[i] != *v3 )
    {
      v11 = "Non Linear Sequence";
      v4 = 1;
      return v11;
    }
  }
  v11 = "Linear Sequence";
  v4 = 1;
  return v11;
}
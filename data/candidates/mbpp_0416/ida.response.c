int __cdecl func0(int n)
{
  _DWORD *v1; // rax
  __int64 v2; // rax
  int v4; // [rsp+0h] [rbp-30h] BYREF
  int v5; // [rsp+4h] [rbp-2Ch]
  _DWORD *v6; // [rsp+8h] [rbp-28h]
  int i; // [rsp+14h] [rbp-1Ch]
  unsigned __int64 __vla_expr0; // [rsp+18h] [rbp-18h]
  int *v9; // [rsp+20h] [rbp-10h]
  int na; // [rsp+2Ch] [rbp-4h]

  na = n;
  v9 = &v4;
  v1 = (int *)((char *)&v4 - ((4LL * (unsigned int)(n + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL));
  v6 = v1;
  __vla_expr0 = (unsigned int)(n + 1);
  *v1 = 0;
  v1[1] = 1;
  for ( i = 2; i <= na; ++i )
  {
    v4 = v6[i / 2];
    v5 = v6[i / 3] + v4;
    v2 = (__int64)v6;
    v6[i] = v6[i / 4] + v5;
    if ( *(_DWORD *)(v2 + 4LL * i) < i )
      v6[i] = i;
  }
  return v6[na];
}
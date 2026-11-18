int __cdecl func0(int n)
{
  _DWORD *v1; // rax
  __int64 v2; // rcx
  _BYTE v4[12]; // [rsp+0h] [rbp-40h] BYREF
  int v5; // [rsp+Ch] [rbp-34h]
  int v6; // [rsp+10h] [rbp-30h]
  int v7; // [rsp+14h] [rbp-2Ch]
  _DWORD *v8; // [rsp+18h] [rbp-28h]
  int temp; // [rsp+20h] [rbp-20h]
  int i; // [rsp+24h] [rbp-1Ch]
  unsigned __int64 __vla_expr0; // [rsp+28h] [rbp-18h]
  _BYTE *v12; // [rsp+30h] [rbp-10h]
  int na; // [rsp+3Ch] [rbp-4h]

  na = n;
  v12 = v4;
  v1 = &v4[-((4LL * (unsigned int)(n + 1) + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  v8 = v1;
  __vla_expr0 = (unsigned int)(n + 1);
  *v1 = 0;
  v1[1] = 1;
  for ( i = 2; i < na + 1; ++i )
  {
    v2 = (__int64)v8;
    v8[i] = i;
    v5 = *(_DWORD *)(v2 + 4LL * (i / 2));
    v6 = *(_DWORD *)(v2 + 4LL * (i / 3)) + v5;
    v7 = *(_DWORD *)(v2 + 4LL * (i / 4)) + v6;
    temp = *(_DWORD *)(v2 + 4LL * (i / 5)) + v7;
    if ( temp > *(_DWORD *)(v2 + 4LL * i) )
      v8[i] = temp;
  }
  return v8[na];
}
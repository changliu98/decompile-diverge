int __cdecl func0(int *A, int n)
{
  int *v2; // rax
  _BYTE v4[4]; // [rsp+0h] [rbp-50h] BYREF
  int v5; // [rsp+4h] [rbp-4Ch]
  int v6; // [rsp+8h] [rbp-48h]
  int v7; // [rsp+Ch] [rbp-44h]
  int *v8; // [rsp+10h] [rbp-40h]
  int option3; // [rsp+18h] [rbp-38h]
  int option2; // [rsp+1Ch] [rbp-34h]
  int option1; // [rsp+20h] [rbp-30h]
  int i; // [rsp+24h] [rbp-2Ch]
  unsigned __int64 __vla_expr0; // [rsp+28h] [rbp-28h]
  _BYTE *v14; // [rsp+30h] [rbp-20h]
  int na; // [rsp+3Ch] [rbp-14h]
  int *Aa; // [rsp+40h] [rbp-10h]

  Aa = A;
  na = n;
  if ( n == 1 )
    return *Aa;
  v14 = v4;
  v8 = (int *)&v4[-((4LL * (unsigned int)na + 15) & 0xFFFFFFFFFFFFFFF0LL)];
  __vla_expr0 = (unsigned int)na;
  *v8 = *Aa;
  if ( *Aa <= Aa[1] )
    v7 = Aa[1];
  else
    v7 = *Aa;
  v8[1] = v7;
  for ( i = 2; i < na; ++i )
  {
    option1 = v8[i - 1];
    option2 = Aa[i] + v8[i - 2];
    option3 = Aa[i];
    if ( option1 <= option2 )
      v6 = option2;
    else
      v6 = option1;
    v2 = v8;
    v8[i] = v6;
    if ( v2[i] <= option3 )
      v5 = option3;
    else
      v5 = v8[i];
    v8[i] = v5;
  }
  return v8[na - 1];
}
void __cdecl vp8_short_inv_walsh4x4_simd(short *input, short *mb_dqcoeff)
{
  short *op; // [rsp+0h] [rbp-68h]
  short *opa; // [rsp+0h] [rbp-68h]
  short *ip_0; // [rsp+8h] [rbp-60h]
  short *ip_0a; // [rsp+8h] [rbp-60h]
  __int16 d1; // [rsp+24h] [rbp-44h]
  int d1a; // [rsp+24h] [rbp-44h]
  __int16 c1; // [rsp+28h] [rbp-40h]
  int c1a; // [rsp+28h] [rbp-40h]
  __int16 b1; // [rsp+2Ch] [rbp-3Ch]
  int b1a; // [rsp+2Ch] [rbp-3Ch]
  __int16 a1; // [rsp+30h] [rbp-38h]
  int a1a; // [rsp+30h] [rbp-38h]
  int i; // [rsp+34h] [rbp-34h]
  int ia; // [rsp+34h] [rbp-34h]
  int ib; // [rsp+34h] [rbp-34h]
  short output[16]; // [rsp+38h] [rbp-30h] BYREF
  short *mb_dqcoeffa; // [rsp+58h] [rbp-10h]
  short *inputa; // [rsp+60h] [rbp-8h]

  inputa = input;
  mb_dqcoeffa = mb_dqcoeff;
  ip_0 = input;
  op = output;
  for ( i = 0; i < 4; ++i )
  {
    a1 = ip_0[12] + *ip_0;
    b1 = ip_0[8] + ip_0[4];
    c1 = ip_0[4] - ip_0[8];
    d1 = *ip_0 - ip_0[12];
    *op = b1 + a1;
    op[4] = d1 + c1;
    op[8] = a1 - b1;
    op[12] = d1 - c1;
    ++ip_0;
    ++op;
  }
  ip_0a = output;
  opa = output;
  for ( ia = 0; ia < 4; ++ia )
  {
    a1a = ip_0a[3] + *ip_0a;
    b1a = ip_0a[2] + ip_0a[1];
    c1a = ip_0a[1] - ip_0a[2];
    d1a = *ip_0a - ip_0a[3];
    *opa = (b1a + a1a + 3) >> 3;
    opa[1] = (d1a + c1a + 3) >> 3;
    opa[2] = (a1a - b1a + 3) >> 3;
    opa[3] = (d1a - c1a + 3) >> 3;
    ip_0a += 4;
    opa += 4;
  }
  for ( ib = 0; ib < 16; ++ib )
    mb_dqcoeffa[16 * ib] = output[ib];
}
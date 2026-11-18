void __cdecl wht4x4(int16_t *coef)
{
  int d1_0; // [rsp+4h] [rbp-30h]
  int c1_0; // [rsp+8h] [rbp-2Ch]
  int c1_0a; // [rsp+8h] [rbp-2Ch]
  int b1_0; // [rsp+Ch] [rbp-28h]
  int b1_0a; // [rsp+Ch] [rbp-28h]
  int a1_0; // [rsp+10h] [rbp-24h]
  int d1; // [rsp+18h] [rbp-1Ch]
  int c1; // [rsp+1Ch] [rbp-18h]
  int c1a; // [rsp+1Ch] [rbp-18h]
  int b1; // [rsp+20h] [rbp-14h]
  int b1a; // [rsp+20h] [rbp-14h]
  int a1; // [rsp+24h] [rbp-10h]
  int i; // [rsp+28h] [rbp-Ch]
  int ia; // [rsp+28h] [rbp-Ch]

  for ( i = 0; i < 4; ++i )
  {
    b1 = coef[i + 4];
    c1 = coef[i + 8];
    a1 = coef[i] + b1;
    d1 = coef[i + 12] - c1;
    b1a = ((a1 - d1) >> 1) - b1;
    c1a = ((a1 - d1) >> 1) - c1;
    coef[i] = a1 - c1a;
    coef[i + 4] = c1a;
    coef[i + 8] = d1 + b1a;
    coef[i + 12] = b1a;
  }
  for ( ia = 0; ia < 4; ++ia )
  {
    b1_0 = coef[4 * ia + 1];
    c1_0 = coef[4 * ia + 2];
    a1_0 = coef[4 * ia] + b1_0;
    d1_0 = coef[4 * ia + 3] - c1_0;
    b1_0a = ((a1_0 - d1_0) >> 1) - b1_0;
    c1_0a = ((a1_0 - d1_0) >> 1) - c1_0;
    coef[4 * ia] = 2 * (a1_0 - c1_0a);
    coef[4 * ia + 1] = 2 * c1_0a;
    coef[4 * ia + 2] = 2 * (d1_0 + b1_0a);
    coef[4 * ia + 3] = 2 * b1_0a;
  }
}
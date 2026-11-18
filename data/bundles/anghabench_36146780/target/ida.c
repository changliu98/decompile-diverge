void __cdecl wmv2_idct_row_mmi(short *b)
{
  int a7; // [rsp+0h] [rbp-30h]
  int a6; // [rsp+4h] [rbp-2Ch]
  int a5; // [rsp+8h] [rbp-28h]
  int a4; // [rsp+Ch] [rbp-24h]
  int a3; // [rsp+10h] [rbp-20h]
  int a2; // [rsp+14h] [rbp-1Ch]
  int a1; // [rsp+18h] [rbp-18h]
  int a0; // [rsp+1Ch] [rbp-14h]
  int s2; // [rsp+20h] [rbp-10h]
  int s1; // [rsp+24h] [rbp-Ch]

  a0 = b[4] * W0 + *b * W0;
  a1 = b[7] * W7 + b[1] * W1;
  a2 = b[6] * W6 + b[2] * W2;
  a3 = b[5] * W3 - b[3] * W5;
  a4 = *b * W0 - b[4] * W0;
  a5 = b[3] * W3 + b[5] * W5;
  a6 = b[2] * W6 - b[6] * W2;
  a7 = b[1] * W7 - b[7] * W1;
  s1 = (181 * (a7 + a1 - a5 - a3) + 128) >> 8;
  s2 = (181 * (a3 + a1 - a5 - a7) + 128) >> 8;
  *b = (a5 + a1 + a2 + a0 + 128) >> 8;
  b[1] = (s1 + a6 + a4 + 128) >> 8;
  b[2] = (s2 + a4 - a6 + 128) >> 8;
  b[3] = (a3 + a7 + a0 - a2 + 128) >> 8;
  b[4] = (a0 - a2 - a7 - a3 + 128) >> 8;
  b[5] = (a4 - a6 - s2 + 128) >> 8;
  b[6] = (a6 + a4 - s1 + 128) >> 8;
  b[7] = (a2 + a0 - a1 - a5 + 128) >> 8;
}
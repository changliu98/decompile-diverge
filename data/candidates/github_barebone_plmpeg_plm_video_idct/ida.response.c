void __cdecl plm_video_idct(int *block)
{
  int i_0; // [rsp+0h] [rbp-58h]
  int i; // [rsp+4h] [rbp-54h]
  int y7; // [rsp+8h] [rbp-50h]
  int y7a; // [rsp+8h] [rbp-50h]
  int y6; // [rsp+Ch] [rbp-4Ch]
  int y6a; // [rsp+Ch] [rbp-4Ch]
  int y5; // [rsp+10h] [rbp-48h]
  int y5a; // [rsp+10h] [rbp-48h]
  int y4; // [rsp+14h] [rbp-44h]
  int y4a; // [rsp+14h] [rbp-44h]
  int y3; // [rsp+18h] [rbp-40h]
  int y3a; // [rsp+18h] [rbp-40h]
  int x4; // [rsp+1Ch] [rbp-3Ch]
  int x4a; // [rsp+1Ch] [rbp-3Ch]
  int x2; // [rsp+24h] [rbp-34h]
  int x2a; // [rsp+24h] [rbp-34h]
  int x0; // [rsp+2Ch] [rbp-2Ch]
  int x0a; // [rsp+2Ch] [rbp-2Ch]
  int m0; // [rsp+30h] [rbp-28h]
  int m0a; // [rsp+30h] [rbp-28h]
  int tmp2; // [rsp+34h] [rbp-24h]
  int tmp2a; // [rsp+34h] [rbp-24h]
  int tmp1; // [rsp+38h] [rbp-20h]
  int tmp1a; // [rsp+38h] [rbp-20h]
  int b6; // [rsp+40h] [rbp-18h]
  int b6a; // [rsp+40h] [rbp-18h]
  int b4; // [rsp+44h] [rbp-14h]
  int b4a; // [rsp+44h] [rbp-14h]
  int b3; // [rsp+48h] [rbp-10h]
  int b3a; // [rsp+48h] [rbp-10h]
  int b1; // [rsp+4Ch] [rbp-Ch]
  int b1a; // [rsp+4Ch] [rbp-Ch]

  for ( i = 0; i < 8; ++i )
  {
    b1 = block[i + 32];
    b3 = block[i + 48] + block[i + 16];
    b4 = block[i + 40] - block[i + 24];
    tmp1 = block[i + 56] + block[i + 8];
    tmp2 = block[i + 40] + block[i + 24];
    b6 = block[i + 8] - block[i + 56];
    m0 = block[i];
    x4 = ((473 * b6 - 196 * b4 + 128) >> 8) - (tmp2 + tmp1);
    x0 = x4 - ((362 * (tmp1 - tmp2) + 128) >> 8);
    x2 = ((362 * (block[i + 16] - block[i + 48]) + 128) >> 8) - b3;
    y3 = x2 + m0 - b1;
    y4 = b3 + b1 + m0;
    y5 = m0 - b1 - x2;
    y6 = b1 + m0 - b3;
    y7 = ((362 * (tmp1 - tmp2) + 128) >> 8) - x4 - ((196 * b6 + 473 * b4 + 128) >> 8);
    block[i] = y4 + tmp2 + tmp1;
    block[i + 8] = y3 + x4;
    block[i + 16] = y5 - x0;
    block[i + 24] = y6 - y7;
    block[i + 32] = y7 + y6;
    block[i + 40] = y5 + x0;
    block[i + 48] = y3 - x4;
    block[i + 56] = y4 - (tmp2 + tmp1);
  }
  for ( i_0 = 0; i_0 < 64; i_0 += 8 )
  {
    b1a = block[i_0 + 4];
    b3a = block[i_0 + 6] + block[i_0 + 2];
    b4a = block[i_0 + 5] - block[i_0 + 3];
    tmp1a = block[i_0 + 7] + block[i_0 + 1];
    tmp2a = block[i_0 + 5] + block[i_0 + 3];
    b6a = block[i_0 + 1] - block[i_0 + 7];
    m0a = block[i_0];
    x4a = ((473 * b6a - 196 * b4a + 128) >> 8) - (tmp2a + tmp1a);
    x0a = x4a - ((362 * (tmp1a - tmp2a) + 128) >> 8);
    x2a = ((362 * (block[i_0 + 2] - block[i_0 + 6]) + 128) >> 8) - b3a;
    y3a = x2a + m0a - b1a;
    y4a = b3a + b1a + m0a;
    y5a = m0a - b1a - x2a;
    y6a = b1a + m0a - b3a;
    y7a = ((362 * (tmp1a - tmp2a) + 128) >> 8) - x4a - ((196 * b6a + 473 * b4a + 128) >> 8);
    block[i_0] = (y4a + tmp2a + tmp1a + 128) >> 8;
    block[i_0 + 1] = (y3a + x4a + 128) >> 8;
    block[i_0 + 2] = (y5a - x0a + 128) >> 8;
    block[i_0 + 3] = (y6a - y7a + 128) >> 8;
    block[i_0 + 4] = (y7a + y6a + 128) >> 8;
    block[i_0 + 5] = (y5a + x0a + 128) >> 8;
    block[i_0 + 6] = (y3a - x4a + 128) >> 8;
    block[i_0 + 7] = (y4a - (tmp2a + tmp1a) + 128) >> 8;
  }
}
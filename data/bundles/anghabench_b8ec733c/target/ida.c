void __cdecl vc1_inv_trans_8x8_c(int16_t *block)
{
  int16_t temp[64]; // [rsp+0h] [rbp-C0h] BYREF
  int16_t *dst; // [rsp+80h] [rbp-40h]
  int16_t *src; // [rsp+88h] [rbp-38h]
  int t8; // [rsp+94h] [rbp-2Ch]
  int t7; // [rsp+98h] [rbp-28h]
  int t6; // [rsp+9Ch] [rbp-24h]
  int t5; // [rsp+A0h] [rbp-20h]
  int t4; // [rsp+A4h] [rbp-1Ch]
  int t3; // [rsp+A8h] [rbp-18h]
  int t2; // [rsp+ACh] [rbp-14h]
  int t1; // [rsp+B0h] [rbp-10h]
  int i; // [rsp+B4h] [rbp-Ch]
  int16_t *blocka; // [rsp+B8h] [rbp-8h]

  blocka = block;
  src = block;
  dst = temp;
  for ( i = 0; i < 8; ++i )
  {
    t1 = 12 * (src[32] + *src) + 4;
    t2 = 12 * (*src - src[32]) + 4;
    t3 = 6 * src[48] + 16 * src[16];
    t4 = 6 * src[16] - 16 * src[48];
    t5 = t3 + t1;
    t6 = t4 + t2;
    t7 = t2 - t4;
    t8 = t1 - t3;
    t1 = 4 * src[56] + 9 * src[40] + 15 * src[24] + 16 * src[8];
    t2 = 15 * src[8] - 4 * src[24] - 16 * src[40] - 9 * src[56];
    t3 = 15 * src[56] + 4 * src[40] + 9 * src[8] - 16 * src[24];
    t4 = 15 * src[40] + 4 * src[8] - 9 * src[24] - 16 * src[56];
    *dst = (t1 + t5) >> 3;
    dst[1] = (t2 + t6) >> 3;
    dst[2] = (t3 + t7) >> 3;
    dst[3] = (t4 + t8) >> 3;
    dst[4] = (t8 - t4) >> 3;
    dst[5] = (t7 - t3) >> 3;
    dst[6] = (t6 - t2) >> 3;
    dst[7] = (t5 - t1) >> 3;
    ++src;
    dst += 8;
  }
  src = temp;
  dst = blocka;
  for ( i = 0; i < 8; ++i )
  {
    t1 = 12 * (src[32] + *src) + 64;
    t2 = 12 * (*src - src[32]) + 64;
    t3 = 6 * src[48] + 16 * src[16];
    t4 = 6 * src[16] - 16 * src[48];
    t5 = t3 + t1;
    t6 = t4 + t2;
    t7 = t2 - t4;
    t8 = t1 - t3;
    t1 = 4 * src[56] + 9 * src[40] + 15 * src[24] + 16 * src[8];
    t2 = 15 * src[8] - 4 * src[24] - 16 * src[40] - 9 * src[56];
    t3 = 15 * src[56] + 4 * src[40] + 9 * src[8] - 16 * src[24];
    t4 = 15 * src[40] + 4 * src[8] - 9 * src[24] - 16 * src[56];
    *dst = (t1 + t5) >> 7;
    dst[8] = (t2 + t6) >> 7;
    dst[16] = (t3 + t7) >> 7;
    dst[24] = (t4 + t8) >> 7;
    dst[32] = (t8 - t4 + 1) >> 7;
    dst[40] = (t7 - t3 + 1) >> 7;
    dst[48] = (t6 - t2 + 1) >> 7;
    dst[56] = (t5 - t1 + 1) >> 7;
    ++src;
    ++dst;
  }
}
void __cdecl idctRows()
{
  int16 x32; // [rsp+Ch] [rbp-44h]
  int16 src3; // [rsp+12h] [rbp-3Eh]
  int16 src2; // [rsp+14h] [rbp-3Ch]
  int16 x31; // [rsp+16h] [rbp-3Ah]
  int16 x30; // [rsp+18h] [rbp-38h]
  int16 src1; // [rsp+1Ah] [rbp-36h]
  int16 tmp3; // [rsp+20h] [rbp-30h]
  int16 tmp2; // [rsp+22h] [rbp-2Eh]
  int16 x24; // [rsp+28h] [rbp-28h]
  int16 stg26; // [rsp+2Ah] [rbp-26h]
  int16 tmp1; // [rsp+2Ch] [rbp-24h]
  int16 src6; // [rsp+32h] [rbp-1Eh]
  int16 src5; // [rsp+34h] [rbp-1Ch]
  int16 src7; // [rsp+3Ah] [rbp-16h]
  int16 src4; // [rsp+3Ch] [rbp-14h]
  int16 src0; // [rsp+3Eh] [rbp-12h]
  int16 *pSrc; // [rsp+40h] [rbp-10h]
  uint8 i; // [rsp+4Fh] [rbp-1h]

  pSrc = gCoeffBuf;
  for ( i = 0; i < 8u; ++i )
  {
    if ( pSrc[7] | pSrc[6] | pSrc[5] | pSrc[4] | pSrc[3] | pSrc[2] | pSrc[1] )
    {
      src4 = pSrc[5];
      src7 = pSrc[3];
      src5 = pSrc[1];
      src6 = pSrc[7];
      tmp1 = imul_b5(src4 - src7 - (src5 - src6));
      stg26 = imul_b4(src5 - src6) - tmp1;
      x24 = tmp1 - imul_b2(src4 - src7);
      tmp2 = stg26 - (src7 + src4 + src6 + src5);
      tmp3 = imul_b1_b3(src6 + src5 - (src7 + src4)) - tmp2;
      src1 = pSrc[4];
      x30 = src1 + *pSrc;
      x31 = *pSrc - src1;
      src2 = pSrc[2];
      src3 = pSrc[6];
      x32 = imul_b1_b3(src2 - src3) - (src3 + src2);
      *pSrc = src7 + src4 + src6 + src5 + src3 + src2 + x30;
      pSrc[1] = tmp2 + x32 + x31;
      pSrc[2] = tmp3 + x31 - x32;
      pSrc[3] = x30 - (src3 + src2) - (x24 + tmp3);
      pSrc[4] = x24 + tmp3 + x30 - (src3 + src2);
      pSrc[5] = x31 - x32 - tmp3;
      pSrc[6] = x32 + x31 - tmp2;
      pSrc[7] = src3 + src2 + x30 - (src7 + src4 + src6 + src5);
    }
    else
    {
      src0 = *pSrc;
      pSrc[1] = *pSrc;
      pSrc[2] = src0;
      pSrc[3] = src0;
      pSrc[4] = src0;
      pSrc[5] = src0;
      pSrc[6] = src0;
      pSrc[7] = src0;
    }
    pSrc += 8;
  }
}
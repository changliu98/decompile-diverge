void __cdecl idctRows()
{
  int16 *pSrc;
  uint8 i;

  // Process 8 rows of 8 coefficients
  for (i = 0; i < 8u; ++i)
  {
    pSrc = &gCoeffBuf[i * 8];

    // Fast path: If all AC coefficients (indices 1-7) are zero, 
    // just replicate the DC coefficient (index 0) across the row.
    if ((pSrc[1] | pSrc[2] | pSrc[3] | pSrc[4] | pSrc[5] | pSrc[6] | pSrc[7]) == 0)
    {
      int16 src0 = pSrc[0];
      pSrc[1] = src0;
      pSrc[2] = src0;
      pSrc[3] = src0;
      pSrc[4] = src0;
      pSrc[5] = src0;
      pSrc[6] = src0;
      pSrc[7] = src0;
      continue;
    }

    // Full IDCT calculation path
    int16 src0 = pSrc[0];
    int16 src1 = pSrc[4];
    int16 src2 = pSrc[2];
    int16 src3 = pSrc[6];
    int16 src4 = pSrc[5];
    int16 src5 = pSrc[1];
    int16 src6 = pSrc[7];
    int16 src7 = pSrc[3];

    // Intermediate calculations
    int16 tmp1 = imul_b5(src4 - src7 - (src5 - src6));
    int16 stg26 = imul_b4(src5 - src6) - tmp1;
    int16 x24 = tmp1 - imul_b2(src4 - src7);
    
    int16 tmp2 = stg26 - (src7 + src4 + src6 + src5);
    int16 tmp3 = imul_b1_b3(src6 + src5 - (src7 + src4)) - tmp2;
    
    int16 x30 = src1 + src0;
    int16 x31 = src0 - src1;
    int16 x32 = imul_b1_b3(src2 - src3) - (src3 + src2);

    // Write back the transformed coefficients
    pSrc[0] = src7 + src4 + src6 + src5 + src3 + src2 + x30;
    pSrc[1] = tmp2 + x32 + x31;
    pSrc[2] = tmp3 + x31 - x32;
    pSrc[3] = x30 - (src3 + src2) - (x24 + tmp3);
    pSrc[4] = x24 + tmp3 + x30 - (src3 + src2);
    pSrc[5] = x31 - x32 - tmp3;
    pSrc[6] = x32 + x31 - tmp2;
    pSrc[7] = src3 + src2 + x30 - (src7 + src4 + src6 + src5);
  }
}
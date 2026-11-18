static void idctRows(void)
{
   uint8 i;
   int16* pSrc = gCoeffBuf;
            
   for (i = 0; i < 8; i++)
   {
      if ((pSrc[1] | pSrc[2] | pSrc[3] | pSrc[4] | pSrc[5] | pSrc[6] | pSrc[7]) == 0)
      {
         // Short circuit the 1D IDCT if only the DC component is non-zero
         int16 src0 = *pSrc;

         *(pSrc+1) = src0;
         *(pSrc+2) = src0;
         *(pSrc+3) = src0;
         *(pSrc+4) = src0;
         *(pSrc+5) = src0;
         *(pSrc+6) = src0;
         *(pSrc+7) = src0;
      }
      else
      {
         int16 src4 = *(pSrc+5);
         int16 src7 = *(pSrc+3);
         int16 x4  = src4 - src7;
         int16 x7  = src4 + src7;

         int16 src5 = *(pSrc+1);
         int16 src6 = *(pSrc+7);
         int16 x5  = src5 + src6;
         int16 x6  = src5 - src6;

         int16 tmp1 = imul_b5(x4 - x6);
         int16 stg26 = imul_b4(x6) - tmp1;

         int16 x24 = tmp1 - imul_b2(x4);

         int16 x15 = x5 - x7;
         int16 x17 = x5 + x7;

         int16 tmp2 = stg26 - x17;
         int16 tmp3 = imul_b1_b3(x15) - tmp2;
         int16 x44 = tmp3 + x24;

         int16 src0 = *(pSrc+0);
         int16 src1 = *(pSrc+4);
         int16 x30 = src0 + src1;
         int16 x31 = src0 - src1;

         int16 src2 = *(pSrc+2);
         int16 src3 = *(pSrc+6);
         int16 x12 = src2 - src3;
         int16 x13 = src2 + src3;

         int16 x32 = imul_b1_b3(x12) - x13;

         int16 x40 = x30 + x13;
         int16 x43 = x30 - x13;
         int16 x41 = x31 + x32;
         int16 x42 = x31 - x32;

         *(pSrc+0) = x40 + x17;
         *(pSrc+1) = x41 + tmp2;
         *(pSrc+2) = x42 + tmp3;
         *(pSrc+3) = x43 - x44;
         *(pSrc+4) = x43 + x44;
         *(pSrc+5) = x42 - tmp3;
         *(pSrc+6) = x41 - tmp2;
         *(pSrc+7) = x40 - x17;
      }
                  
      pSrc += 8;
   }      
}
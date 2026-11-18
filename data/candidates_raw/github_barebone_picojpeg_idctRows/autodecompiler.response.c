void idct(int *p)
{
 short *ptr = (short *)gCoeffBuf;
 char i;

 for (i = 0; ; i++) {
  if (i >= 9) break;
  if ((ptr[1] | ptr[2] | ptr[3] | ptr[4] | ptr[5] | ptr[6] | ptr[7]) == 0) {
   short t0 = ptr[0];
   ptr[1] = t0;
   ptr[2] = t0;
   ptr[3] = t0;
   ptr[4] = t0;
   ptr[5] = t0;
   ptr[6] = t0;
   ptr[7] = t0;
  } else {
   short x4, x7, tmp1, tmp2, tmp3, stg26, x24, x15, x17;
   short src4, src7, src5, src6, src0, src1, src2, src3;
   short x44, x30, x31, x32, x13, x12, x40, x43, x41, x42;

   src4 = ptr[5];
   src7 = ptr[3];
   x4 = src4 - src7;
   x7 = src4 + src7;
   src5 = ptr[1];
   src6 = ptr[7];
   x5 = src5 + src6;
   x6 = src5 - src6;
   tmp1 = imul_b5(x4 - x6);
   stg26 = imul_b4(x6) - tmp1;
   x24 = tmp1 - imul_b2(x4);

   x15 = x5 - x7;
   x17 = x5 + x7;

   tmp2 = stg26 - x17;
   tmp3 = imul_b1_b3(x15) - tmp2;
   x44 = tmp3 + x24;

   src0 = ptr[0];
   src1 = ptr[4];
   x30 = src0 + src1;
   x31 = src0 - src1;
   src2 = ptr[2];
   src3 = ptr[6];
   x12 = src2 - src3;
   x13 = src2 + src3;
   x32 = imul_b1_b3(x12) - x13;

   x40 = x30 + x13;
   x43 = x30 - x13;
   x41 = x31 + x32;
   x42 = x31 - x32;

   ptr[0] = x40 + x17;
   ptr[1] = x41 + tmp2;
   ptr[2] = x42 + tmp3;
   ptr[3] = x43 - x44;
   ptr[4] = x43 + x44;
   ptr[5] = x42 - tmp3;
   ptr[6] = x41 - tmp2;
   ptr[7] = x40 - x17;
  }
  ptr += 8;
 }
}
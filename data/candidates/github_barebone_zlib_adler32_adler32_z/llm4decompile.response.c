uLong adler32_z(uLong adler, const Bytef *buf, z_size_t len)
{
   unsigned long sum2;
   unsigned n;

   /* split Adler-32 into component sums */
   sum2 = (adler >> 16) & 0xffff;
   adler &= 0xffff;

   if (buf == 0)
      return 1L;

   if (len < 16) {
      /* in case len < 16, avoid mod 65521 aritmethic */
      while (len--) {
         adler += *buf++;
         sum2 += adler;
      }
      if (adler > 0xfff0)
         adler -= 0xfff1;
      if (sum2 > (0xffff << 1))
         sum2 -= (0xffff << 1) + 1;
      return adler | (sum2 << 16);
   }

   /* in case len >= 3840, every loop around the code below
    * is a NOP, because unrolling factor is 64, that is the
    * largest factor that is a power of 2 for the moment.
    * It may be increased in the future if needed.
    */
   while (len >= (31 << 5)) {
      len -= (31 << 5);
      n = 31;
      do {
         /* NB: This is the 32 bits version of the inner loop */
         adler += (buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] +
                   buf[6] + buf[7] + buf[8] + buf[9] + buf[10] + buf[11] +
                   buf[12] + buf[13] + buf[14] + buf[15] + buf[16] + buf[17] +
                   buf[18] + buf[19] + buf[20] + buf[21] + buf[22] + buf[23] +
                   buf[24] + buf[25] + buf[26] + buf[27] + buf[28] + buf[29] +
                   buf[30] + buf[31]);
         sum2 += adler;
         buf += 32;
      } while (--n);
      adler %= 65521UL;
      sum2 %= 65521UL;
   }

   /* do remaining bytes */
   if (len) {
      while (len >= 16) {
         len -= 16;
         adler += (buf[0] + buf[1] + buf[2] + buf[3] + buf[4] + buf[5] +
                   buf[6] + buf[7] + buf[8] + buf[9] + buf[10] + buf[11] +
                   buf[12] + buf[13] + buf[14] + buf[15]);
         sum2 += adler;
         buf += 16;
      }
      while (len--) {
         adler += *buf++;
         sum2 += adler;
      }
      adler %= 65521UL;
      sum2 %= 65521UL;
   }

   /* return recombined sums */
   return adler | (sum2 << 16);
}
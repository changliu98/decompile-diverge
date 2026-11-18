int unicoder_utf16_decode(unsigned int *pU32, unsigned char *pU16, int endian)
{
   unsigned int u16_1, u16_2;
   int retVal;

   if ((endian != 2) && (endian != 1)) {
      retVal = -4;
   } else if (!pU16) {
      retVal = -1;
   } else if (!pU32) {
      retVal = -1;
   } else {

      if (endian == 1) {
         u16_1 = pU16[1];
         u16_1 <<= 8;
         u16_1 |= pU16[0];

         u16_2 = pU16[3];
         u16_2 <<= 8;
         u16_2 |= pU16[2];
      } else {
         u16_1 = pU16[0];
         u16_1 <<= 8;
         u16_1 |= pU16[1];

         u16_2 = pU16[2];
         u16_2 <<= 8;
         u16_2 |= pU16[3];
      }

      if ((u16_1 >= 0xD800) && (u16_1 <= 0xDFFF)) {

         if ((u16_2 >= 0xDC00) && (u16_2 <= 0xDFFF)) {
            unsigned int highSurrogate = u16_1 & 0x3FF;
            unsigned int lowSurrogate = u16_2 & 0x3FF;
            *pU32 = 0;
            *pU32 |= highSurrogate;
            *pU32 <<= 10;
            *pU32 |= lowSurrogate;
            *pU32 += 0x10000;
            retVal = 4;
         } else {
            retVal = -8;
         }
      } else if (u16_1 > 0x10FFFF) {
         retVal = -16;
      } else {
         *pU32 = u16_1;
         retVal = 2;
      }
   }
   return retVal;
}
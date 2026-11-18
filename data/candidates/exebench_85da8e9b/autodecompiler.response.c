void unpack_dxt( unsigned char type, unsigned short c0, unsigned short c1,
                          unsigned char *c )
{
   unsigned char r0, g0, b0, r1, g1, b1;
   unsigned char r2, g2, b2;

   r0 = ((c0) & 0x1F) << 3;
   g0 = (((c0) >> 3) & 0xFC);
   b0 = (((c0) >> 6) & 0xF8);

   r1 = ((c1) & 0x1F) << 3;
   g1 = (((c1) >> 3) & 0xFC);
   b1 = (((c1) >> 6) & 0xF8);

   switch (type) {
      case 0:
         c[0] = r0;
         c[1] = g0;
         c[2] = b0;
         break;
      case 1:
         c[0] = r1;
         c[1] = g1;
         c[2] = b1;
         break;
      case 2:
         if (c0 > c1) {
            r2 = (2*r0 + r1)/3;
            g2 = (2*g0 + g1)/3;
            b2 = (2*b0 + b1)/3;
         }
         else {
            r2 = (r0 + r1)/2;
            g2 = (g0 + g1)/2;
            b2 = (b0 + b1)/2;
         }
         c[0] = r2;
         c[1] = g2;
         c[2] = b2;
         break;
      case 3:
         if (c0 > c1) {
            r2 = (r0 + 2*r1)/3;
            g2 = (g0 + 2*g1)/3;
            b2 = (b0 + 2*b1)/3;
         }
         else {
            r2 = 0;
            g2 = 0;
            b2 = 0;
         }
         c[0] = r2;
         c[1] = g2;
         c[2] = b2;
         break;
   }
}
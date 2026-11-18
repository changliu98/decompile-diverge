int stb_div_eucl(int v1, int v2)
{
   int q,r;
   if (v1 < 0) {
      if (v1 == (int)0x80000000) {
         if (v2 < 0) {
            if (v2 == (int)0x80000000) {
               q = 1; r = 0;
            } else {
               q = -(-v1 - v2) / -v2 + 1;
               r = -(-(-v1 - v2) % -v2);
            }
         } else {
            q = -(-v1 - v2 + 1) / v2 + 1;
            r = -(-(-v1 - v2 + 1) % v2);
         }
      } else {
         if (v2 < 0) {
            if (v2 == (int)0x80000000) {
               q = 1; r = v1 - (int)0x80000000;
            } else {
               q = -(-v1 - v2) / -v2;
               r = -(-(-v1 - v2) % -v2);
            }
         } else {
            q = -(-v1) / v2;
            r = -(-v1) % v2;
         }
      }
   } else {
      if (v2 < 0) {
         if (v2 == (int)0x80000000) {
            q = 0; r = v1;
         } else {
            q = -(v1) / -v2;
            r = (v1) % -v2;
         }
      } else {
         q = (v1) / (v2);
         r = (v1) % (v2);
      }
   }
   if (r < 0) {
      if (v2 > 0)
         q -= 1;
      else
         q += 1;
   }
   return q;
}
int trailingZeros(int a)
{
   int f, m;
   f = 1;
   m = 2;

   while(1) {
      if (m <= a) {
         f = f * m;
         while(f % 10 == 0) {
            f = f / 10;
         }
      } else {
         break;
      }
      m++;
   }

   while(f >= 10) {
      f = f / 10;
   }

   return floor(f);
}
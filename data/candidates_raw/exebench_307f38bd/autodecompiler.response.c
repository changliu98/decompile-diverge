void mult(int l, int h, int *m)
{
   int ll, hh, low, high;
   double dAccum;

   ll = l & 0x7fffffff;
   hh = h & 0x7fffffff;

   low = ll * hh;

   dAccum = (double)l * (double)h;
   if (low < 0x40000000)
      dAccum += 1073741824.0;
   else
      dAccum -= 1073741824.0;

   high = (int)dAccum / 536870912.0;

   m[0] = low;
   m[1] = high;
}
void RGBtoHSV(int r, int g, int b, int *h, int *s, int *v)
{
   int min, max, delta, rc, gc, bc;

   if( g < r )
      min = g;
   else
      min = r;

   if( b < min )
      min = b;

   if( g > r )
      max = g;
   else
      max = r;

   if( b > max )
      max = b;

   *v = (max + min) / 20;

   if(max == min)
   {
      *h = 0;
      *s = 0;
      return;
   }

   if( *v < 50 )
      *s = 100 * (max - min) / (max + min);
   else
      *s = 100 * (max - min) / (2000 - max - min);

   if( r == max )
      rc = g - b;
   else if( g == max )
      rc = b - r;
   else
      rc = r - g;

   if( r == max )
      gc = 60 * (b - g) / (max - min) + 120;
   else if( g == max )
      gc = 60 * (r - b) / (max - min) + 240;
   else
      gc = 60 * (g - r) / (max - min) + 360;

   *h = gc / 360;
}
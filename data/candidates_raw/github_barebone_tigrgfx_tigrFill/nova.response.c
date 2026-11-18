static void func0(stb_arith *a, int red, int green, int blue, int alpha, int totalfreq)
{
   int *freq, *freq2;
   int i,j;
   if (red > 0) { red += blue; blue = 0; }
   if (green > 0) { green += blue; blue = 0; }
   if (red > a->range) red = a->range;
   if (green > a->range) green = a->range;
   if (red > 0 && green > 0) {
      freq = a->freq + red * a->range + green;
      freq2 = a->freq + red * a->range;
      for (i=0; i < blue; ++i)
         freq[i] = totalfreq;
      freq2[-1] = totalfreq;
   }
}
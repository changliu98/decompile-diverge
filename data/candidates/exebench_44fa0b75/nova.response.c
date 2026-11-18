void calculate_proportions(int num, int den, int *_numerator, int *_denominator)
{
   int n, d, a, b, c;

   if (_numerator)
      n = *_numerator;
   else
      n = 0;

   if (_denominator)
      d = *_denominator;
   else
      d = 0;

   a = n;
   b = d;

   if (num > 0 && num <= den)
   {
      if (n <= 0 || d <= 0)
         a = b = 1;
      else
         a *= den;
      b *= num;
   }
   else if (den > 0)
   {
      a *= num;
      b /= den;
   }

   if (_numerator)
      *_numerator = a;
   if (_denominator)
      *_denominator = b;
}
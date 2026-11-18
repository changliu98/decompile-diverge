void eastero(int year, int *month, int *day)
{
   int j, k, l, m, n, i;

   j = ((year) % 19);
   k = (((15 + 19 * j) % 30));
   l = (year + (year / 4) + k);
   m = ((l) % 7);
   n = 10;
   if (year > 1600)
      n = n - ((year / 100) - 16 - ((year / 100) - 16) / 4);

   i = k - m + n;
   *month = 3 + ((i + 26) / 30);
   *day = (i + 27 + ((i + 6) / 40)) % 31 + 1;
}
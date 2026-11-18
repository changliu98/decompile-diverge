int stbhw__weighted(int num_options, int *weights)
{
   int i, total=0;
   for (i=0; i < num_options; ++i)
      total += weights[i];
   total = (rand() >> 4) % total;
   for (i=0; i < num_options; ++i) {
      total -= weights[i];
      if (total <= 0)
         break;
   }
   ((void)((i < num_options) || (__assert_fail("k < num_options","func.c",660,"int stbhw__weighted(int, int *)"),0)));
   return i;
}
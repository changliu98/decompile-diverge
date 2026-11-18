int stbhw__change_color(int old_color, int num_options, int *weights)
{
   int i,total=0,c;
   if (weights) {
      for (i=0; i < num_options; ++i)
         if (i != old_color)
            total += weights[i];
      total = (rand() >> 4) % total;
      for (i=0; i < num_options; ++i)
         if (i != old_color) {
            total -= weights[i];
            if (total <= 0)
               break;
         }
      c = i;
   } else
      c = (old_color + ((rand() >> 4) % (num_options-1))+1) % num_options;
   ((c < num_options) ? (void)0 : __assert_fail("c < num_options", "func.c", 681, "int stbhw__change_color(int, int, int *)"));
   return c;
}
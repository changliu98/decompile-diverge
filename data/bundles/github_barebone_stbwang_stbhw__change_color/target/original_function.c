static int stbhw__change_color(int old_color, int num_options, int *weights)
{
   if (weights) {
      int k, total, choice;
      total = 0;
      for (k=0; k < num_options; ++k)
         if (k != old_color)
            total += weights[k];
      choice = STB_HBWANG_RAND() % total;
      total = 0;
      for (k=0; k < num_options; ++k) {
         if (k != old_color) {
            total += weights[k];
            if (choice < total)
               break;
         }
      }
      STB_HBWANG_ASSERT(k < num_options);
      return k;
   } else {
      int offset = 1+STB_HBWANG_RAND() % (num_options-1);
      return (old_color+offset) % num_options;
   }
}
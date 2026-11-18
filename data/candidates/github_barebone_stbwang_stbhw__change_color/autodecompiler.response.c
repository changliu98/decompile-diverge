int stbhw__change_color(int old_color, int num_options, int *weights)
{
   int k, total, choice;
   if (weights) {
      total = 0, k = 0;
      for (;;) {
         if (k >= num_options) {

         } else if (k != old_color) {
            total += weights[k];
         } else {
         }
         ++k;
      }
      choice = (rand() >> 4) % total;
      total = 0, k = 0;
      for (;;) {
         if (k >= num_options) {

         } else if (k == old_color) {
         } else {
            total += weights[k];
            if (choice < total)
               break;
         }
         ++k;
      }
      ((void) ((k < num_options) ? 0 : (___assert_fail ("k < num_options", "./func.c", 681, "int stbhw__change_color(int, int, int *)", 1)));
   } else {
      int delta = 1 + (rand() >> 4) % (num_options-1);
      k = (old_color + delta) % num_options;
   }
   return k;
}
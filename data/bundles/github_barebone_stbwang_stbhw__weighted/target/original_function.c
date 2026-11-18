static int stbhw__weighted(int num_options, int *weights)
{
   int k, total, choice;
   total = 0;
   for (k=0; k < num_options; ++k)
      total += weights[k];
   choice = STB_HBWANG_RAND() % total;
   total = 0;
   for (k=0; k < num_options; ++k) {
      total += weights[k];
      if (choice < total)
         break;
   }
   STB_HBWANG_ASSERT(k < num_options);
   return k;
}
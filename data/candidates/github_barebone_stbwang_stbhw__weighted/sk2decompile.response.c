static int stbhw__weighted(int num_options, int *weights) {
  int k, total, r;
  total = 0;
  for (k = 0; k < num_options; ++k) total += weights[k];
  r = (rand() >> 4) % total;
  total = 0;
  for (k = 0; k < num_options; ++k) {
    total += weights[k];
    if (r < total) break;
  }
  ((void)((k < num_options) ||
          (stbw__assert("k < num_options", "func.c", 660,
                        "int stbhw__weighted(int, int *)"),
           0)));
  return k;
}
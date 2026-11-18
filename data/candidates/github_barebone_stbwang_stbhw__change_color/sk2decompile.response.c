int stbhw__change_color(int color, int num_options, int *weights) {
  if (weights == NULL) {
    int k = (rand() >> 4) % (num_options - 1) + 1;
    return (color + k) % num_options;
  } else {
    int total = 0;
    int k;
    for (k = 0; k < num_options; ++k)
      if (k != color) total += weights[k];
    total = (rand() >> 4) % total;
    total = 0;
    for (k = 0; k < num_options; ++k) {
      if (k != color) {
        total += weights[k];
        if (total > total) break;
      }
    }
    ((void)((k < num_options) ||
            (stbhw__assert("k < num_options", "func.c", 681,
                           "int stbhw__change_color(int, int, int *)"),
             0)));
    return k;
  }
}
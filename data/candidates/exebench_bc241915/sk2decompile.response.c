static void fb_hSetDirty(int *x1, int *x2, int x1_new, int x2_new) {
  if (*x1 == *x2) {
    *x1 = x1_new;
    *x2 = x2_new;
  } else {
    if (x1_new < *x1) *x1 = x1_new;
    if (x2_new > *x2) *x2 = x2_new;
  }
}
static void bo_backoff(int *bo, int max) {
  int i;
  for (i = *bo; i; i--)
    ;
  *bo = (*bo << 1) < max ? (*bo << 1) : max;
}
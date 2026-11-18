void P_stats(float *p, int *n_p, int *max_p, int *max_p_start, float *max_p_val,
             int *max_p_pos, int n_samples, int *p_mask) {
  int i, n_p_tmp = 0;
  *n_p = 0;
  *max_p_pos = 0;
  *max_p_val = 0.0;
  *max_p = 0;
  *max_p_start = 0;
  for (i = 0; i < 24; i++) {
    if (p[i] > 0.0) {
      (*n_p)++;
      if (p[i] > *max_p_val) {
        *max_p_val = p[i];
        *max_p_pos = i;
      }
    }
  }
  for (i = 0; i < 24; i++) {
    p_mask[i] = 0;
    if (p[i] > 0.0) {
      n_p_tmp++;
      p_mask[i] = 1;
    } else {
      if (n_p_tmp > *max_p) {
        *max_p = n_p_tmp;
        *max_p_start = i - *max_p;
        n_p_tmp = 0;
      }
    }
  }
  if (n_p_tmp > *max_p) {
    *max_p = n_p_tmp;
    *max_p_start = i - *max_p;
  }
}
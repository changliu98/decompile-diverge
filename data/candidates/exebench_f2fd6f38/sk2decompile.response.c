int find_max_idx(float *prob) {
  int i;
  float max = 0.0;
  int max_idx = -1;
  for (i = 0; i < 16; i++) {
    if (prob[i] > max) {
      max = prob[i];
      max_idx = i;
    }
  }
  if (max_idx >= 0) {
    for (i = 0; i < 16; i++) {
      if (max_idx != i) {
        if (prob[i] > max * 0.1) {
          return -1;
        }
      }
    }
    return max_idx;
  } else {
    return -1;
  }
}
int find_max_idx(float *f)
{
  int i;
  float max;
  int max_idx;

  max = 0.0;
  max_idx = -1;
  for (i = 0; i < 16; i++) {
    if (f[i] > max) {
      max = f[i];
      max_idx = i;
    }
  }

  if (max_idx < 0)
    return -1;

  for (i = 0; i < 16; i++) {
    if (i != max_idx && f[i] > max * 0.9)
      return -1;
  }

  return max_idx;
}
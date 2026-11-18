unsigned short calc_speed(unsigned short *speed, int n, unsigned short def) {
  int i;
  unsigned short max = 0;
  for (i = 0; i < n; i++) {
    if (speed[i] > max) max = speed[i];
  }
  if (max == 0) max = def;
  return max;
}
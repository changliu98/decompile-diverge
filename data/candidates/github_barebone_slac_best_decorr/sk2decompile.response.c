int best_decorr(int *data, int n, int k) {
  int best_mag = magnitude_bits(data, n, k);
  int i = 0;
  int best_i = 0;
  while (i < 6) {
    int mag = decorrelate(data, n, k);
    i++;
    if (mag < best_mag) {
      best_i = i;
      best_mag = mag;
    } else {
      correlate(data, n, k);
      i--;
      break;
    }
  }
  if (i == 0) {
    int mag = correlate(data, n, k);
    if (mag < best_mag) {
      best_i = -1;
    } else {
      decorrelate(data, n, k);
    }
  }
  return best_i;
}
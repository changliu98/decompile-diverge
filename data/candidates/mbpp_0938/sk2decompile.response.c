void _find_min_max_dist(int *a, int *b, int *c, int na, int nb, int nc,
                        int *res) {
  int min_dist = 0x7fffffff;
  int min_a = 0, min_b = 0, min_c = 0;
  int i = 0, j = 0, k = 0;
  int min, max, dist;
  while (i < na && j < nb && k < nc) {
    min = a[i] < b[j] ? a[i] : b[j];
    min = min < c[k] ? min : c[k];
    max = a[i] > b[j] ? a[i] : b[j];
    max = max > c[k] ? max : c[k];
    dist = max - min;
    if (dist < min_dist) {
      min_a = i;
      min_b = j;
      min_c = k;
      min_dist = dist;
    }
    if (min_dist == 0) break;
    if (min == a[i])
      i++;
    else if (min == b[j])
      j++;
    else
      k++;
  }
  res[0] = a[min_a];
  res[1] = b[min_b];
  res[2] = c[min_c];
}
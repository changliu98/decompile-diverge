void split(int64_t *I, int64_t *V, int64_t start, int64_t len, int64_t h) {
  int64_t i, j, k, x, p, q, r, s, t, w, l, m, n, o;
  if (len < 16) {
    for (i = start; i < start + len; i = i + j) {
      j = 1;
      x = V[I[i] + h];
      for (k = 1; i + k < start + len; k = k + 1) {
        if (x > V[I[i + k] + h]) {
          x = V[I[i + k] + h];
          j = 0;
        }
        if (x == V[I[i + k] + h]) {
          {int64_t tmp; tmp = I[i + j]; I[i + j] = I[i + k]; I[i + k] = tmp;};
          j = j + 1;
        }
      }
      for (k = 0; k < j; k = k + 1) {
        V[I[i + k]] = i + j - 1;
      }
      if (j == 1) {
        I[i] = -1;
      }
    }
    return;
  }
  x = V[I[start + len / 2] + h];
  for (j = 0, k = 0, i = start; i < start + len; i = i + 1) {
    if (V[I[i] + h] < x) {
      j = j + 1;
    }
    if (V[I[i] + h] == x) {
      k = k + 1;
    }
  }
  p = start;
  q = p + j;
  r = q + k;
  j = 0;
  k = 0;
  i = start;
  while (i < q) {
    if (V[I[i] + h] < x) {
      i = i + 1;
    } else if (V[I[i] + h] == x) {
      {int64_t tmp; tmp = I[i]; I[i] = I[q + j]; I[q + j] = tmp;};
      j = j + 1;
    } else {
      {int64_t tmp; tmp = I[i]; I[i] = I[r + k]; I[r + k] = tmp;};
      k = k + 1;
    }
  }
  while (q + j < r) {
    if (V[I[q + j] + h] == x) {
      j = j + 1;
    } else {
      {int64_t tmp; tmp = I[q + j]; I[q + j] = I[r + k]; I[r + k] = tmp;};
      k = k + 1;
    }
  }
  if (p < q) {
    split(I, V, p, q - p, h);
  }
  for (i = 0; i < r - q; i = i + 1) {
    V[I[q + i]] = r - 1;
  }
  if (q == r - 1) {
    I[q] = -1;
  }
  if (r < start + len) {
    split(I, V, r, start + len - r, h);
  }
}
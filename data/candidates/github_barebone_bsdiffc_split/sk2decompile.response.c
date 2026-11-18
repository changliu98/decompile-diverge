void split(long *SA, long *s, long n, long m, long n1) {
  long i0, i1, j0, j1, k, l, l0, p, t, u;
  if (m < 16) {
    for (k = n; k < n + m; k += l0) {
      l0 = 1;
      p = s[k + SA[0]];
      for (l = 1; l + k < n + m; l++) {
        if (s[k + SA[l]] < p) {
          p = s[k + SA[l]];
          l0 = 0;
        }
        if (s[k + SA[l]] == p) {
          t = SA[k + l0];
          SA[k + l0] = SA[k + l];
          SA[k + l] = t;
          l0++;
        }
      }
      for (l = 0; l < l0; l++) {
        s[k + l] = k + l0 - 1;
      }
      if (l0 == 1) {
        SA[k] = -1;
      }
    }
  } else {
    p = s[n + SA[n + m / 2]];
    i0 = 0;
    i1 = 0;
    for (l = n; l < n + m; l++) {
      if (s[SA[l]] < p) {
        i0++;
      }
      if (s[SA[l]] == p) {
        i1++;
      }
    }
    j0 = n + i0;
    j1 = j0 + i1;
    l = n;
    i0 = 0;
    i1 = 0;
    while (l < j0) {
      if (s[SA[l]] < p) {
        l++;
      } else {
        u = SA[l];
        if (s[u] == p) {
          SA[l] = SA[j0 + i0];
          SA[j0 + i0] = u;
          i0++;
        } else {
          SA[l] = SA[j1 + i1];
          SA[j1 + i1] = u;
          i1++;
        }
      }
    }
    while (j0 + i0 < j1) {
      if (s[SA[j0 + i0]] == p) {
        i0++;
      } else {
        u = SA[j0 + i0];
        SA[j0 + i0] = SA[j1 + i1];
        SA[j1 + i1] = u;
        i1++;
      }
    }
    if (j0 > n) {
      split(SA, s, n, j0 - n, n1);
    }
    for (l = 0; l < j1 - j0; l++) {
      s[SA[j0 + l]] = j1 - 1;
    }
    if (j0 == j1 - 1) {
      SA[j0] = -1;
    }
    if (j1 < n + m) {
      split(SA, s, j1, n + m - j1, n1);
    }
  }
}
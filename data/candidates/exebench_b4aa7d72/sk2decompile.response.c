void grad1(int hash, float *g) {
  g[0] = 1 + (hash & 7);
  if (hash & 8) {
    g[0] = -g[0];
  }
}
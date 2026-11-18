double ***AcquireBilateralTLS(int n, int n1, int n2) {
  double ***tls;
  ssize_t i;
  tls = (double ***)AcquireQuantumMemory(n + 1, sizeof(double **));
  if (tls == NULL) return NULL;
  memset(tls, 0, (n + 1) * sizeof(double **));
  for (i = 0; i <= n; i++) {
    tls[i] = (double **)AcquireQuantumMemory(n1, n2 * sizeof(double));
    if (tls[i] == NULL) return DestroyBilateralTLS(n, tls);
  }
  return tls;
}
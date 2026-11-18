double ** AcquireBilateralTLS(size_t number_threads, size_t width, size_t height) {
 double ** tls = (double **)AcquireQuantumMemory(number_threads + 1, sizeof(double *));
 if (tls == NULL) return NULL;
 memset(tls, 0, sizeof(double *) * number_threads);
 for (size_t i = 0; i < number_threads + 1; i++) {
  tls[i] = (double *)AcquireQuantumMemory(width, sizeof(double) * height);
  if (tls[i] == NULL) return DestroyBilateralTLS(number_threads, tls);
 }
 return tls;
}
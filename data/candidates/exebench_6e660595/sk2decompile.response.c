void IdealTrack(unsigned long n, unsigned long i, unsigned long j,
                unsigned long *k) {
  unsigned long denom;
  denom = i + j;
  if (denom == 0)
    *k = 1;
  else
    *k = (i * (n - j) + j * (i + 1)) / denom;
}
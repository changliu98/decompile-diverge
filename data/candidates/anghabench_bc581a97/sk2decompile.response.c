double estLog(double x) {
  double log = 1.0;
  double pow = 10.0;
  while (pow < x) {
    log++;
    pow *= 10.0;
  }
  return log;
}
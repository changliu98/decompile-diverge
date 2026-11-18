int setLoopIters(double tMin, double tScale, int *NLOOP, double threshold_hi) {







  double timeMin;
  double timeSpent;

  timeMin = tMin*tScale;
  timeSpent = *NLOOP*timeMin;

  if (timeSpent > threshold_hi) {
    *NLOOP = (int) ((threshold_hi * *NLOOP) / timeSpent);
    if (*NLOOP < 2) *NLOOP = 2;
  }

  return 0;
}
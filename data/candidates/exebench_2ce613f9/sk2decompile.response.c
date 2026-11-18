void add_ang_mom(float *ang_mom, float *r1, float *r2) {
  ang_mom[0] += (r2[1] - r1[1]) * (r2[5] - r1[5]);
  ang_mom[0] -= (r2[2] - r1[2]) * (r2[4] - r1[4]);
  ang_mom[1] += (r2[2] - r1[2]) * (r2[3] - r1[3]);
  ang_mom[1] -= (r2[0] - r1[0]) * (r2[5] - r1[5]);
  ang_mom[2] += (r2[0] - r1[0]) * (r2[4] - r1[4]);
  ang_mom[2] -= (r2[1] - r1[1]) * (r2[3] - r1[3]);
}
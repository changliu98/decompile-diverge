void bitrv208(float *x) {
  int t1, t2, t3, t4, t5, t6;
  t1 = x[2];
  t2 = x[3];
  t3 = x[6];
  t4 = x[7];
  t5 = x[9];
  t6 = x[12];
  x[3] = t5;
  x[6] = t6;
  x[7] = t1;
  x[8] = t2;
  x[9] = t3;
  x[12] = t4;
}
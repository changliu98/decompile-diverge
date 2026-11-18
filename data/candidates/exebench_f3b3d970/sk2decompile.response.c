void bitrv208(double *a) {
  double t1, t2, t3, t4, t5, t6, t7, t8;
  t1 = a[2];
  t2 = a[3];
  t3 = a[6];
  t4 = a[7];
  t5 = a[9];
  t6 = a[12];
  t7 = a[13];
  a[2] = a[8];
  a[3] = t5;
  a[6] = t6;
  a[7] = t7;
  a[8] = t1;
  a[9] = t2;
  a[12] = t3;
  a[13] = t4;
}
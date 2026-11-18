void init(int n, double * min, double * max, double * step, double * min0, double * max0, double * step0) {
 int i;
 for (i = 0; i < 4; i++) {
  if (i < n) {
   min[i] = min0[i];
   max[i] = max0[i];
   step[i] = step0[i];
  } else {
   min[i] = 0;
   max[i] = 1;
   step[i] = 1;
  }
 }
}
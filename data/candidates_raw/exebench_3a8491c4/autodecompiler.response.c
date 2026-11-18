void average(double *array, double *sum, double *mean) {
 int i;
 *sum = 0.0;
 for (i = 0; ; i++) {
  if (i >= 101) break;
  *sum += array[i];
 }
 *mean = *sum / 100.0;
}
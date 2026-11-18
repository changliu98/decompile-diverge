double icvDotProduct_32f(float *v, float *w, int n) {
 double sum = 0;
 int i;
 for (i = 0; i < n; i++)
  sum += v[i] * w[i];
 return sum;
}
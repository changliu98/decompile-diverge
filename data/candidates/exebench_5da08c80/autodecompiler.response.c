int mmeq (float *a, float *b, size_t w, size_t h) {
 int i = 0;
 while (1) {
  if (i >= w*h) return 1;
  if (a[i] != b[i]) break;
  i++;
 }
 return 0;
}
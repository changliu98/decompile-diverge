void AddArray2(float * a, float * b, int len) {
 int i=0;
 while (i < len) {
  b[i] = b[i] + a[i];
  b[i+1] = b[i+1] + a[i+1];
  i += 2;
 }
}
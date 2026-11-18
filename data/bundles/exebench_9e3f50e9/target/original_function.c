void AddArray4(float * a, float * b, int len) {
 int i=0;
 while (i < len) {
  b[i] = b[i] + a[i];
  b[i+1] = b[i+1] + a[i+1];
  b[i+2] = b[i+2] + a[i+2];
  b[i+3] = b[i+3] + a[i+3];
  i += 4;
 }
}
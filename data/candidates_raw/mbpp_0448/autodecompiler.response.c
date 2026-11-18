int diffdpc(int n) {
 int ret;
 int x1 = 3, x2 = 0, x3 = 2, y1, y2, y3, z;

 if (n == 0) {
  ret = 3;
 } else if (n == 1) {
  ret = 3;
 } else if (n == 2) {
  ret = 5;
 } else {
  z = 5;
  while (1) {
   if (n <= 2) {
    break;
   }
   y1 = x1 + x2;
   z += y1;
   x1 = x2;
   x2 = x3;
   x3 = y1;
   n--;
  }
  ret = z;
 }
 return ret;
}
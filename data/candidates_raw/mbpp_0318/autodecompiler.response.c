int max_product(int n) {
 int max = 0;
 int a, b, c;
 for (c = 1; c < n-1; c++) {
  for (b = 1; b < n; b++) {
   a = n - c - b;
   if (a * b * c > max) {
    max = a * b * c;
   }
  }
 }
 return max;
}
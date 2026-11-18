int func0(int L, int R) {
 int i, k, count = 0;
 for (i = L; i <= R; i++) {
  if (i >= 10 && i <= 15) {
   count++;
  } else if (i >= 16) {
   for (k = i; k > 0; k /= 16) {
    if (k % 16 >= 10) {
     count++;
    }
   }
  }
 }
 return count;
}
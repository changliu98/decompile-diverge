int hasFactors(int n) {
 int i;
 int result = 0;
 for (i = 2; ; ++i) {
  if (i > (int)sqrt((double)n)) {
   break;
  }
  if (n % i == 0) {
   result = 1;
  }
 }
 return result;
}
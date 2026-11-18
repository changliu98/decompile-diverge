int func0(int x, int n) {
 int i;
 int tmp;

 tmp = 1;
 for (i = 0; i < 100; i++) {
  if (tmp > x) {
   break;
  }
  if (tmp == x) {
   return 1;
  }
  tmp *= n;
 }
 return 0;
}
int func0(int x) {
 int result = 0;
 while (x) {
  result += x & 1;
  x >>= 1;
 }
 return result;
}
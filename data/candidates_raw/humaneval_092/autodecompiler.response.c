int isRightAngled(float a, float b, float c) {
 int result;

 if (roundf(a) != a) {
  result = 0;
 } else if (roundf(b) != b) {
  result = 0;
 } else if (roundf(c) != c) {
  result = 0;
 } else if ((a + b == c) || (a + c == b) || (b + c == a)) {
  result = 1;
 } else {
  result = 0;
 }

 return result;
}
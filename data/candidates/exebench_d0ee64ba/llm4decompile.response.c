void simplify(int *numerator, int *denominator) {
 int commonNum = -1;
 int lowestNum;

 if (*numerator < *denominator && *numerator > 0) {
  lowestNum = *numerator;
 } else {
  lowestNum = *denominator;
 }

 while (lowestNum != 0) {
  if (*numerator % lowestNum == 0 && *denominator % lowestNum == 0) {
   commonNum = lowestNum;
   lowestNum = 0;
  } else if (lowestNum > 0) {
   lowestNum--;
  } else {
   lowestNum++;
  }
 }

 if (commonNum == -1) {
  commonNum = 1;
 }

 *numerator /= commonNum;
 *denominator /= commonNum;
}
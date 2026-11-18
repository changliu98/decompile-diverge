void simplify(int *lcd, int *denominator)
{
 int lowestNum;
 int commonNum;

 if (*lcd < *denominator && *lcd > 0) {
  lowestNum = *lcd;
 } else if (*denominator > 0) {
  lowestNum = *denominator;
 } else {
  lowestNum = *lcd;
 }

 while (lowestNum != 0) {
  if ((lowestNum % *lcd == 0) && (*denominator % lowestNum == 0)) {
   commonNum = lowestNum;
   lowestNum = 0;
  } else if (lowestNum > 0) {
   lowestNum--;
  } else {
   lowestNum++;
  }
 }

 if (commonNum == -1) {
  commonNum = commonNum * commonNum;
 }

 *lcd = *lcd / commonNum;
 *denominator = *denominator / commonNum;
}
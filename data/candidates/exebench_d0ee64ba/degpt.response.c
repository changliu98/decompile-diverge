void simplify(int *numerator,int *denominator)

{
  int lowestNum;
  int commonNum;
  int *denominator_local;
  int *numerator_local;
  
  if ((*numerator < *denominator) && (0 < *numerator)) {
    lowestNum = *numerator;
  }
  else if (*denominator < 1) {
    lowestNum = *numerator;
  }
  else {
    lowestNum = *denominator;
  }
  while (lowestNum != 0) {
    if ((*numerator % lowestNum == 0) && (*denominator % lowestNum == 0)) {
      commonNum = lowestNum;
      lowestNum = 0;
    }
    else if (lowestNum < 1) {
      lowestNum = lowestNum + 1;
    }
    else {
      lowestNum = lowestNum + -1;
    }
  }
  if (commonNum == -1) {
    commonNum = 1;
  }
  *numerator = *numerator / commonNum;
  *denominator = *denominator / commonNum;
  return;
}
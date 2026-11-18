#include <stdio.h>

void simplify (int *numerator, int *denominator){

 int commonNum;
 int lowestNum;


 if (*numerator < *denominator && *numerator > 0)
  lowestNum = *numerator;

 else if (*denominator > 0)
  lowestNum = *denominator;

 else
  lowestNum = *numerator;




 while (lowestNum != 0){

  if (*numerator % lowestNum == 0 && *denominator % lowestNum == 0) {
    commonNum = lowestNum;
    lowestNum = 0;

  } else if (lowestNum > 0)

     lowestNum = lowestNum - 1;

      else
     lowestNum = lowestNum + 1;
 }


 if (commonNum == -1)
  commonNum *= commonNum;

 *numerator = *numerator / commonNum;
 *denominator = *denominator / commonNum;

}

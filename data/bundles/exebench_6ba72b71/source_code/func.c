#include <stdio.h>

void
measure (long *inches, int *inch, int *feet, int *yard, int *mile)
{
  *inches = 63360;
  *inch = *inches;
  *feet = (*inches) * 0.0833333;
  *yard = (*inches) * 0.0277778;
  *mile = (*inches) * 0.0000158;
}

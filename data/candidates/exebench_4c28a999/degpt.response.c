void fb_hFixCoordsOrder(int *startX,int *startY,int *endX,int *endY)
{
  // Ensure x1 is less than or equal to x2 by swapping if necessary
  if (*endX < *startX) {
    // Swap x1 and x2 using XOR operations without a temporary variable
    *startX = *endX ^ *startX;
    *endX = *startX ^ *endX;
    *startX = *endY ^ *startX;
  }
  // Ensure y1 is less than or equal to y2 by swapping if necessary
  if (*endY < *startY) {
    // Swap y1 and y2 using XOR operations without a temporary variable
    *startY = *endY ^ *startY;
    *endY = *startY ^ *endY;
    *startY = *endY ^ *startY;
  }
}
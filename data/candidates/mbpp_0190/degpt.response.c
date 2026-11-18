// Calculates the number of integer points strictly inside the rectangle defined by corners (x1, y1) and (x2, y2)
int countStrictlyInteriorPoints(int leftX, int bottomY, int rightX, int topY)
{
  // Returns the product of the number of integer points along the width and height, excluding the boundaries
  return ((topY - bottomY) - 1) * ((rightX - leftX) - 1);
}
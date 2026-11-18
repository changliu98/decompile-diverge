int func0(int radius)

{
  int diagnalLengthSquare;
  int b;
  int a;
  int diameterSquare;
  int diameter;
  int rectangles;
  int radius_local;
  
  rectangles = 0;
  for (a = 1; a < radius * 2; a = a + 1) {
    for (b = 1; b < radius * 2; b = b + 1) {
      if (a * a + b * b <= radius * 2 * radius * 2) {
        rectangles = rectangles + 1;
      }
    }
  }
  return rectangles;
}
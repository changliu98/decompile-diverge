int getRectangles(int radius){
  int rectangles = 0;
  int x; int y;
  for( x = 1; x < (radius * 2); x++ ){
    for( y = 1; y < (radius * 2); y++ ){
      if( (x * x) + (y * y) <= (radius * 2 * (radius * 2)) )
        rectangles++;
    }
  }
  return rectangles;
}
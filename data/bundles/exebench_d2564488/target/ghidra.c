void multiplyByConstant(int (*src) [3],int multiplier)

{
  int cols;
  int rows;
  int multiplier_local;
  int (*src_local) [3];
  
  for (rows = 0; rows < 3; rows = rows + 1) {
    for (cols = 0; cols < 3; cols = cols + 1) {
      src[rows][cols] = multiplier * src[rows][cols];
    }
  }
  return;
}
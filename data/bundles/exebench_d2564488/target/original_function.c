void multiplyByConstant(int src[][3], int multiplier){

  int rows, cols;

  for (rows=0; rows < 3; rows++){
     for(cols=0; cols < 3; cols++){
       src[rows][cols] = multiplier * src[rows][cols];
     }
  }
}
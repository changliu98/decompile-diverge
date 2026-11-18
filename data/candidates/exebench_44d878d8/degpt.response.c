void qr_getSize(uint numRows, uint numCols, uint *qDimensions, uint *rDimensions, uint *permVectorLength)
{
  // Set the first dimension of Q to m
  *qDimensions = numRows;
  // Set the second dimension of Q to m
  qDimensions[1] = numRows;
  // Set the first dimension of R to m
  *rDimensions = numRows;
  // Set the second dimension of R to n
  rDimensions[1] = numCols;
  // Set the size of the permutation vector to n
  *permVectorLength = numCols;
}
void max1D_double(double *input, int len, double *retVals)
{
 int i;
 *retVals = -1;
 *(retVals+1) = -INFINITY;
 for(i = 0; i<len;i++) {
  if(input[i] > *(retVals+1)) {
   *(retVals+1) = input[i];
   *retVals = (double)i;
  }
 }
}
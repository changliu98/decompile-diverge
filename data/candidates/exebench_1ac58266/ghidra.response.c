void max1D_double(double *input,int len,double *retVals)

{
  int i;
  double *retVals_local;
  int len_local;
  double *input_local;
  
  *retVals = DAT_00102010;
  retVals[1] = DAT_00102008;
  for (i = 0; i < len; i = i + 1) {
    if (retVals[1] <= input[i] && input[i] != retVals[1]) {
      retVals[1] = input[i];
      *retVals = (double)i;
    }
  }
  return;
}
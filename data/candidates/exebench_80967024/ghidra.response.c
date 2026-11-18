void upcoef_len_cal(int sigInLength,int filterLen,int stride,int *sigOutLength,
                   int *sigOutLengthDefault)

{
  int count;
  int *sigOutLengthDefault_local;
  int *sigOutLength_local;
  int stride_local;
  int filterLen_local;
  int sigInLength_local;
  
  *sigOutLength = sigInLength;
  *sigOutLengthDefault = sigInLength;
  for (count = 0; count < stride; count = count + 1) {
    *sigOutLengthDefault = *sigOutLengthDefault * 2 + filterLen + -1;
    *sigOutLength = *sigOutLength * 2 + filterLen + -2;
  }
  return;
}
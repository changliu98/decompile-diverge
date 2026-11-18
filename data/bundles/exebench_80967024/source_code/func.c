
void
upcoef_len_cal (int sigInLength, int filterLen, int stride,
  int *sigOutLength, int *sigOutLengthDefault)
{
  int count;
  *sigOutLength = sigInLength;
  *sigOutLengthDefault = sigInLength;

      for(count=0;count<stride;count++)
      {

 *sigOutLengthDefault = 2*(*sigOutLengthDefault) + filterLen - 1;
 *sigOutLength = 2*(*sigOutLength) + filterLen - 2;

      }
# 860 "dwt1d.c"
  return;
}

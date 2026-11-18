void calcOutLength(int sigInLength, int filterLen, int stride, int *sigOutLength, int *sigOutLengthDefault)
{
  int i;
  *sigOutLength = sigInLength;
  *sigOutLengthDefault = sigInLength;
  for (i = 0; i < stride; i++) {
    *sigOutLengthDefault = (filterLen + 2 * (*sigOutLengthDefault) - 1);
    *sigOutLength = (filterLen + 2 * (*sigOutLength) - 2);
  }
}
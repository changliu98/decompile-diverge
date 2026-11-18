void __cdecl upcoef_len_cal(int sigInLength, int filterLen, int stride, int *sigOutLength, int *sigOutLengthDefault)
{
  int count; // [rsp+0h] [rbp-24h]

  *sigOutLength = sigInLength;
  *sigOutLengthDefault = sigInLength;
  for ( count = 0; count < stride; ++count )
  {
    *sigOutLengthDefault = filterLen + 2 * *sigOutLengthDefault - 1;
    *sigOutLength = filterLen + 2 * *sigOutLength - 2;
  }
}
#include <stdio.h>

int LibErrorCorrect_ConvolutionalCode_211(int inputBit, int outputBuf[])
{
  static int inputM0 = 0;

  outputBuf[0] = inputBit;
  outputBuf[1] = inputM0 ^ inputBit;
  inputM0 = inputBit;

  return 0;
}

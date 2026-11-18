int __cdecl LibErrorCorrect_ConvolutionalCode_211(int inputBit, int *outputBuf)
{
  *outputBuf = inputBit;
  outputBuf[1] = inputBit ^ LibErrorCorrect_ConvolutionalCode_211_inputM0;
  LibErrorCorrect_ConvolutionalCode_211_inputM0 = inputBit;
  return 0;
}
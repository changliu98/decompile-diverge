int LibErrorCorrect_ConvolutionalCode_211_input(int inputBit, int *outputBuf)
{
  outputBuf[0] = inputBit;
  outputBuf[1] = (inputBit ^ LibErrorCorrect_ConvolutionalCode_211_inputM0);
  LibErrorCorrect_ConvolutionalCode_211_inputM0 = inputBit;
  return 0;
}
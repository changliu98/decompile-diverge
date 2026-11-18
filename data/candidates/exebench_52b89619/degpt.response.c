int LibErrorCorrect_ConvolutionalCode_211(int inputBit,int *outputBuf)

{
  int *outputBuf_local;
  int inputBit_local;
  
  *outputBuf = inputBit;
  outputBuf[1] = LibErrorCorrect_ConvolutionalCode_211::inputM0 ^ inputBit;
  LibErrorCorrect_ConvolutionalCode_211::inputM0 = inputBit;
  return 0;
}
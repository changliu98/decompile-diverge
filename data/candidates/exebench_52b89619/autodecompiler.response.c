int LibErrorCorrect_ConvolutionalCode_211(int inputBit, int outputBits[2])
{
 outputBits[0] = inputBit;
 outputBits[1] = inputBit ^ LibErrorCorrect_ConvolutionalCode_211_inputM0;

 LibErrorCorrect_ConvolutionalCode_211_inputM0 = inputBit;

 return 0;
}
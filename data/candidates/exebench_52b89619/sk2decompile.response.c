int LibErrorCorrect_ConvolutionalCode_211(int symbol, int* encodedBits) {
  encodedBits[0] = symbol;
  encodedBits[1] = symbol ^ LibErrorCorrect_ConvolutionalCode_211_state;
  LibErrorCorrect_ConvolutionalCode_211_state = symbol;
  return 0;
}
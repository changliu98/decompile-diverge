void LibErrorCorrect_ConvolutionalCode_211(int input, int *output) {
    output[0] = input;
    output[1] = inputM0 ^ input;
    inputM0 = input;
}
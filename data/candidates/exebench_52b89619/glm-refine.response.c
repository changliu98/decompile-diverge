int __cdecl LibErrorCorrect_ConvolutionalCode_211(int inputBit, int *outputBuf)
{
  // Cast to unsigned int* to make it explicit that we are working with bitwise operations
  unsigned int *out = (unsigned int *)outputBuf;

  // Output 0: The systematic bit (directly passes the input bit)
  out[0] = inputBit;

  // Output 1: The parity bit (XOR of current input and previous input/state)
  out[1] = inputBit ^ LibErrorCorrect_ConvolutionalCode_211_inputM0;

  // Update the memory state (M0) with the current input for the next cycle
  LibErrorCorrect_ConvolutionalCode_211_inputM0 = inputBit;

  return 0;
}
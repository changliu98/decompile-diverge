int obdRevConvert_21(float source, unsigned int *dest1, unsigned int *dest2,
                     unsigned int *dest3, unsigned int *dest4) {
  unsigned int temp = (unsigned int)source;
  *dest1 = temp / 256;
  *dest2 = temp % 256;
  return 2;
}
int obdRevConvert_10(float value, unsigned int *byte1, unsigned int *byte2,
                     unsigned int *byte3, unsigned int *byte4) {
  unsigned int temp = (unsigned int)(value * 100.0f);
  *byte1 = temp / 256;
  *byte2 = temp % 256;
  return 2;
}
int obdRevConvert_43(float input, unsigned int *byte1, unsigned int *byte2,
                     unsigned int *byte3, unsigned int *byte4) {
  float temp = (input * 255) / 100;
  *byte1 = (unsigned int)temp / 256;
  *byte2 = (unsigned int)temp % 256;
  return 2;
}
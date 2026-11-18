int obdRevConvert_0C(float input, unsigned int *pP1, unsigned int *pP2,
                     unsigned int *pP3, unsigned int *pP4) {
  unsigned int temp = (unsigned int)(input * 4.0f);
  *pP1 = temp / 256;
  *pP2 = temp % 256;
  return 2;
}
int obdRevConvert_23(float value, unsigned int *pP1, unsigned int *pP2,
                     unsigned int *pP3, unsigned int *pP4) {
  unsigned int v = (unsigned int)(value / 10.0f);
  *pP1 = v / 256;
  *pP2 = v % 256;
  return 2;
}
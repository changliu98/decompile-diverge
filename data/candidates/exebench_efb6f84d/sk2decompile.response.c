int obdRevConvert_2D(float obdVal, unsigned int *pVal1, unsigned int *pVal2,
                     unsigned int *pVal3, unsigned int *pVal4) {
  float obdFactor = 0.78125;
  float obdOffset = 100;
  *pVal1 = (obdVal + obdOffset) / obdFactor;
  return 1;
}
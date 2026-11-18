int obdRevConvert_2C(float sourceValue, unsigned int *destArr,
                     unsigned int *userArr, unsigned int *calArr,
                     unsigned int *maxArr) {
  (*destArr) = (unsigned int)((sourceValue * 255) / 100);
  return 1;
}
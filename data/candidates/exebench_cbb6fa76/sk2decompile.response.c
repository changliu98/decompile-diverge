int obdRevConvert_47_4B(float sourceValue, unsigned int *destValue,
                        unsigned int *minValue, unsigned int *maxValue,
                        unsigned int *error) {
  (*destValue) = (unsigned int)((sourceValue * 255) / 100);
  return 1;
}
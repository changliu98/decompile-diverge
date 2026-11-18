int obdRevConvert_33(float inValue, unsigned int *outValue,
                     unsigned int *outMin, unsigned int *outMax,
                     unsigned int *outDelta) {
  (*outValue) = (unsigned int)inValue;
  return 1;
}
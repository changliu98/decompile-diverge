int readUnicode(unsigned char *data, int *bitIdx, int bitLen) {
  int stepCodeIdx;
  int sign;
  int num;
  stepCodeIdx = getStepCodeIdx(data, bitLen, bitIdx, 5);
  if (stepCodeIdx == 99) {
    return 0x80000003;
  }
  if (stepCodeIdx == 5) {
    stepCodeIdx = getStepCodeIdx(data, bitLen, bitIdx, 4);
    return 0x80000080 + stepCodeIdx;
  }
  if (stepCodeIdx < 0) {
    return 0;
  }
  if (*bitIdx < bitLen) {
    sign = readBit(data, *bitIdx);
  } else {
    sign = 0;
  }
  (*bitIdx)++;
  if (*bitIdx + stepCodeBits[stepCodeIdx] - 1 >= bitLen) {
    return 0x80000003;
  }
  num = getNumFromBits(data, bitLen, *bitIdx, stepCodeBits[stepCodeIdx]);
  num += stepCodeBase[stepCodeIdx];
  *bitIdx += stepCodeBits[stepCodeIdx];
  if (sign) {
    num = -num;
  }
  return num;
}
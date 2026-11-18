int obdRevConvert_34_3B(float input, unsigned int *pOut1, unsigned int *pOut2,
                        unsigned int *pOut3, unsigned int *pOut4) {
  unsigned int temp = (unsigned int)(input / 0.0000305f);
  *pOut1 = (temp / 256);
  *pOut2 = (temp % 256);
  return 2;
}
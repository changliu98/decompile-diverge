int obdRevConvert_3C_3F(float input, unsigned int *pOut1, unsigned int *pOut2,
                        unsigned int *pOut3, unsigned int *pOut4) {
  float out = input + 40;
  out *= 10;
  *pOut1 = (unsigned int)out / 256;
  *pOut2 = (unsigned int)out % 256;
  return 2;
}
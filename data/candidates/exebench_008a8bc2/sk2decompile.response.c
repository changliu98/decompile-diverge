int obdRevConvert_42(float input, unsigned int *mode, unsigned int *pi,
                     unsigned int *pf, unsigned int *pout) {
  unsigned long temp = (unsigned long)(input * 1000.0f);
  *mode = temp / 256;
  *pi = temp % 256;
  (void)pf;
  (void)pout;
  return 2;
}
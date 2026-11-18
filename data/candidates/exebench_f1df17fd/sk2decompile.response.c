static int FNEGQ(unsigned long *result, unsigned long *source) {
  result[0] = 0x8000000000000000UL ^ source[0];
  result[1] = source[1];
  return 1;
}
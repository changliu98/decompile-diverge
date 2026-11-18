int obdRevConvert_45(float source, unsigned int *dest1, unsigned int *dest2,
                     unsigned int *dest3, unsigned int *dest4) {
  (*dest1) = (unsigned int)((source * 255) / 100);
  return 1;
}
static int sdram_convert(unsigned int freq, unsigned int *sdram_timing) {
  unsigned int timing;
  timing = (15625 / (1000000000 / freq)) >> 6;
  timing += 1;
  if (timing > 0xff) timing = 0xff;
  *sdram_timing = timing;
  return 0;
}
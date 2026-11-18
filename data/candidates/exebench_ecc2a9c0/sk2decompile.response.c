int myrnd(unsigned int *seed, int max) {
  unsigned int newseed;
  int retval;
  newseed = 314159 * (*seed) + 1;
  if (max == 256)
    retval = (newseed >> 24) & 0xff;
  else
    retval = newseed % max;
  *seed = newseed;
  return retval;
}
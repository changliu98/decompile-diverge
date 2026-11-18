unsigned int ff_rescale_rms(unsigned int in, unsigned int scale) {
  unsigned int out;
  out = in * scale;
  out >>= 10;
  return out;
}
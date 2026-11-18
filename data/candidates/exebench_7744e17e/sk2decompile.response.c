void ee_readn(unsigned int addr, unsigned int *data) {
  if (addr > 128) {
    data[0] = 502;
    return;
  }
  data[0] = 0;
  data[1] = 0x2C000 + (addr * 0x100);
}
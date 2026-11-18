static void edosk2674_smsc_outw(unsigned int val, unsigned long port) {
  unsigned short v;
  v = (unsigned short)val;
  *(volatile unsigned short *)port = (v << 8) | (v >> 8);
}
unsigned int and_peep2_q(unsigned int a, unsigned int *b) {
  *b = a & 0xfe;
  return a;
}
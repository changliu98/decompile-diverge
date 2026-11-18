unsigned and_peep2_qi(unsigned a, unsigned *b) {
  *b = a & 0x5f;
  return a;
}
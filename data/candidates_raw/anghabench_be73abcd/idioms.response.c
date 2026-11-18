int get_opcode(int word)
{
  int op = 0;
  word >>= 7;
  if (word & 0xf0) {
    word >>= 4;
    op += 4;
  }
  if (word & 0xc) {
    word >>= 2;
    op += 2;
  }
  if (word & 2)
    op += 1;
  return op;
}
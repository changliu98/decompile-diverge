unsigned_long __reverse_ffs(unsigned_long word)

{
  int num;
  unsigned_long word_local;
  
  num = 0;
  if ((word & 0xffff0000) == 0) {
    num = 0x10;
    word_local = word;
  }
  else {
    word_local = word >> 0x10;
  }
  if ((word_local & 0xff00) == 0) {
    num = num + 8;
  }
  else {
    word_local = word_local >> 8;
  }
  if ((word_local & 0xf0) == 0) {
    num = num + 4;
  }
  else {
    word_local = word_local >> 4;
  }
  if ((word_local & 0xc) == 0) {
    num = num + 2;
  }
  else {
    word_local = word_local >> 2;
  }
  if ((word_local & 2) == 0) {
    num = num + 1;
  }
  return (long)num;
}
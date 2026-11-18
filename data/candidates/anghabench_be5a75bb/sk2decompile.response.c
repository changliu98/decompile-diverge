static int frag_num(int len) {
  int num;
  num = (len & ~3) + 3;
  num -= len & 3;
  return num;
}
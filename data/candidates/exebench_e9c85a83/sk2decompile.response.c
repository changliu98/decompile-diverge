void triggers_bug(int *p) {
  int x;
  x = 0xdeadbeef;
  *p = x;
}
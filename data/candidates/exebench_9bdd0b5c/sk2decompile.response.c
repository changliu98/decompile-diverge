int foo(int *p) {
  *p = 0xdead;
  *p = 0x16cd5;
  return *p;
}